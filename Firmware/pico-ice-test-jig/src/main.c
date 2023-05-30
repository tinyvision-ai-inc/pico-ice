/*
 * MIT License
 *
 * Copyright (c) 2023 tinyVision.ai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// libc
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// pico-sdk
#include "hardware/irq.h"

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_led.h"
#include "ice_sram.h"

#define FIRST_GPIO_PIN      0
#define LAST_GPIO_PIN       29
#define FPGA_BUTTON_PIN     ICE_FPGA_21_PIN // Mirrored from the FPGA
#define FPGA_HIGH_Z_PIN     ICE_FPGA_20_PIN
#define CHAIN_IN_PIN        ICE_FPGA_26_PIN
#define CHAIN_OUT_PIN       ICE_FPGA_27_PIN

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(*(x)))

static bool g_step_failed;
static bool g_test_failed;
static bool g_any_failed;

const enum {
    TYPE_FREE_PIN = 0,
    TYPE_FPGA_PIN,
    TYPE_SPI_PIN,
    TYPE_LED_PIN,
    TYPE_SYSTEM_PIN,
} pin_type[30] = {
    // shared Pmod pins
    [0]     = TYPE_FPGA_PIN,
    [1]     = TYPE_FPGA_PIN,
    [2]     = TYPE_FPGA_PIN,
    [3]     = TYPE_FPGA_PIN,
    [4]     = TYPE_FPGA_PIN,
    [5]     = TYPE_FPGA_PIN,
    [6]     = TYPE_FPGA_PIN,
    [7]     = TYPE_FPGA_PIN,

    // SPI pins
    [8]     = TYPE_SPI_PIN,
    [9]     = TYPE_SPI_PIN,
    [10]    = TYPE_SPI_PIN,
    [11]    = TYPE_SPI_PIN,
    [14]    = TYPE_SPI_PIN,

    // LED pins
    [ICE_LED_RED_PIN]       = TYPE_LED_PIN,
    [ICE_LED_GREEN_PIN]     = TYPE_LED_PIN,
    [ICE_LED_BLUE_PIN]      = TYPE_LED_PIN,

    // system pins
    [FPGA_BUTTON_PIN]       = TYPE_SYSTEM_PIN,
    [FPGA_HIGH_Z_PIN]       = TYPE_SYSTEM_PIN,
    [ICE_FPGA_CRESET_B_PIN] = TYPE_SYSTEM_PIN,
    [ICE_FPGA_CDONE_PIN]    = TYPE_SYSTEM_PIN,

    // FPGA clock pin
    [24]    = TYPE_FPGA_PIN,
};

static void test_sleep_ms(uint32_t delay_ms) {
    for (uint32_t i = 0; i < delay_ms; i += 1) {
        tud_task();
        ice_usb_sleep_ms(1);
    }
}

static void test_assert(bool exp) {
    if (!exp) {
        g_step_failed = true;
        g_test_failed = true;
        g_any_failed = true;
    }
}

static void test_step_printf(char const *fmt, ...)
{
    va_list va;

    va_start(va, fmt);
    printf(" %s - ", g_step_failed ? "FAIL" : "PASS");
    vprintf(fmt, va);
    printf("\n");
}

static bool test_start(char const *desc) {
    printf("\n%s\n", desc);
    g_test_failed = false;
}

static void test_end(void) {
    if (!g_test_failed) {
        printf(" PASS\n");
    }
}

static void test_summary(void (*led_fn)(bool)) {
    if (g_any_failed) {
        ice_led_init();
        ice_led_red(true);
        printf("\nFAIL - Some tests above failed\n");
    } else {
        ice_led_init();
        led_fn(true);
        printf("\nPASS - All tests passed\n");
    }
}

static bool pull_output(uint pin, bool state) {
    // change state of SWDIO or SWCLK using pull-up and pull-down
    int pulls = state ? PADS_BANK0_GPIO0_PUE_BITS : PADS_BANK0_GPIO0_PDE_BITS;
    hw_write_masked(&padsbank0_hw->io[pin], pulls, PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS);
}

static bool button_pressed(void) {
    test_sleep_ms(1);
    return !gpio_get(FPGA_BUTTON_PIN);
}

static bool pin_is_drivable(uint8_t pin) {
    switch (pin_type[pin]) {
    case TYPE_SYSTEM_PIN:
        return false;
    default:
        return true;
    }
}

static bool pin_is_pulled_externally(uint8_t pin) {
    switch (pin_type[pin]) {
    case TYPE_SPI_PIN:
    case TYPE_LED_PIN:
    case TYPE_SYSTEM_PIN:
        return true;
    default:
        return false;
    }
}

static bool pin_set_all_input(void) {
    for (int i = FIRST_GPIO_PIN; i <= LAST_GPIO_PIN; i++) {
        gpio_init(i);
    }
}

static bool button_wait_press_release(void) {
    while (!button_pressed());
    while (button_pressed());
}

static bool fpga_pins_high_z(bool state) {
    gpio_put(FPGA_HIGH_Z_PIN, state);
}

static bool check_pin_state(int pin, bool state) {
    g_step_failed = false;
    test_assert(gpio_get(pin) == state);
    test_step_printf("%s(%d, %s)", __func__, pin, state ? "true" : "false");
}

static void check_pin_connected(int pin_i, int pin_o) {
    g_step_failed = false;
    gpio_set_dir(pin_o, GPIO_OUT);
    gpio_set_dir(pin_i, GPIO_IN);
    gpio_disable_pulls(pin_i);

    for (int i = 0; i < 10; i++) {
        gpio_put(pin_o, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(pin_i) == 0);

        gpio_put(pin_o, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(pin_i) == 1);
    }

    test_step_printf("%s(%d, %d)", __func__, pin_i, pin_o);
    gpio_set_dir(pin_o, GPIO_IN);
}

static void check_pin_not_connected(int pin_i, int pin_o) {
    g_step_failed = false;
    gpio_set_dir(pin_o, GPIO_OUT);
    gpio_set_dir(pin_i, GPIO_IN);
    gpio_set_pulls(pin_i, true, false);

    for (int i = 0; i < 10; i++) {
        gpio_put(pin_o, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(pin_i) == 1);

        gpio_put(pin_o, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(pin_i) == 1);
    }

    test_step_printf("%s(%d, %d)", __func__, pin_i, pin_o);
    gpio_set_dir(pin_o, GPIO_IN);
    gpio_disable_pulls(pin_i);
}

static void check_free_pin_consistent(int pin) {
    g_step_failed = false;
    gpio_set_dir(pin, GPIO_IN);

    for (int i = 0; i < 10; i++) {
        gpio_set_pulls(pin, true, false); // pull up
        test_sleep_ms(1);
        test_assert(gpio_get(pin) == 1);

        gpio_set_pulls(pin, false, true); // pull down
        test_sleep_ms(1);
        test_assert(gpio_get(pin) == 0);
    }

    test_step_printf("%s(%d)", __func__, pin);
}

static void check_pulled_pin_consistent(int pin) {
    g_step_failed = false;
    gpio_set_dir(pin, GPIO_OUT);

    for (int i = 0; i < 10; i++) {
        gpio_put(pin, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(pin) == 1);

        gpio_put(pin, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(pin) == 0);
    }

    test_step_printf("%s(%d)", __func__, pin);
    gpio_set_dir(pin, GPIO_IN);
}

static const uint8_t dummy_range[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x1C, 0x2D, 0x2E, 0x2F,
};

static const uint8_t dummy_zero[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void run_test_out_of_jig(void) {
    uint8_t id[8];
    uint8_t buf[sizeof(dummy_range)];

    // check that GPIOs are connected to themselves,
    // verifying e.g. that they are not bridged to power nets
    test_start("RP2040 pin self-test");
    for (int i = FIRST_GPIO_PIN; i <= LAST_GPIO_PIN; ++i) {
        if (pin_is_drivable(i)) {
            if (pin_is_pulled_externally(i)) {
                check_pulled_pin_consistent(i);
            } else {
                check_free_pin_consistent(i);
            }
        }
    }
    test_end();

    // check adjacent GPIOs are not bridged.
    test_start("RP2040 pin not bridged");
    for (int i1 = FIRST_GPIO_PIN, i2 = i1 + 1; i2 <= LAST_GPIO_PIN; i1++, i2++) {
        if (!pin_is_pulled_externally(i2) && pin_is_drivable(i1)) {
            check_pin_not_connected(i2, i1);
        }
        if (!pin_is_pulled_externally(i1) && pin_is_drivable(i2)) {
            check_pin_not_connected(i1, i2);
        }
    }
    test_end();

    // check the SRAM Known Good Die (KGD) self-test status
    test_start("SRAM chip ID");
    ice_sram_init();
    ice_sram_get_id(id);
    test_assert(id[0] == 0x0D);
    test_assert(id[1] == 0x5D);
    test_step_printf("chip_id=0x%02X%02X%02X%02X%02X%02X%02X%02X",
        id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7]);
    test_end();

    // check a few pages
    test_start("SRAM chip read/write");
    for (uint32_t addr = 0; addr < 64 * 1024; addr += 123) {

        ice_sram_write_blocking(addr, dummy_range, sizeof(dummy_range));
        ice_sram_read_blocking(addr, buf, sizeof(buf));
        test_assert(memcmp(buf, dummy_range, sizeof(buf)) == 0);

        ice_sram_write_blocking(addr, dummy_zero, sizeof(dummy_zero));
        ice_sram_read_blocking(addr, buf, sizeof(buf));
        test_assert(memcmp(buf, dummy_zero, sizeof(buf)) == 0);

        test_step_printf("addr=0x%06X", addr);
    }
    test_end();
}

static void run_test_in_jig(void) {

    test_start("RP2040 pin pairs");

    /*
     *             │
     * GPIO28█───█GPIO13
     *             │
     * GPIO29█───█GPIO12
     *     ┌───────┤
     * GPIO16█───█GPIO20
     *     │       │
     * GPIO17█───█GPIO21
     *     │       │
     * GPIO18█───█GPIO22
     *     │       │
     * GPIO19█───█GPIO23
     *     │       │
     */
    check_pin_connected(28, 13);
    check_pin_connected(29, 12);
    check_pin_connected(16, 20);
    check_pin_connected(17, 21);
    check_pin_connected(18, 22);
    check_pin_connected(19, 23);

    /*
     *     ┌─:─────┤
     * ICE_25█───█ICE_23
     *     │     : │
     * ICE_19█───█ICE_18
     *     │ :     │
     */
    check_pin_connected(ICE_FPGA_25_PIN, ICE_FPGA_23_PIN);
    check_pin_connected(ICE_FPGA_19_PIN, ICE_FPGA_18_PIN);

    test_end();

    test_start("iCE40 pin chain");

    /*
     *        │     : │
     * <--ICE_27█   █ICE_26<--
     *        │.'     │
     */
    fpga_pins_high_z(false);
    check_pin_connected(ICE_FPGA_27_PIN, ICE_FPGA_26_PIN);
    fpga_pins_high_z(true);

    test_end();
}

int main(void) {
    stdio_init_all();
    tusb_init();

    // initial state of all pins
    pin_set_all_input();

    // configure extra pins states with the SDK
    ice_led_init();
    ice_fpga_init(48);
    ice_fpga_start();

    // adjust some pins after the SDK configuration
    gpio_init(ICE_FPGA_CLOCK_PIN);
    gpio_set_dir(FPGA_HIGH_Z_PIN, GPIO_OUT);

    // prevent the FPGA from interfering
    fpga_pins_high_z(true);

    // tests run outside of the test jig
    button_wait_press_release();
    run_test_out_of_jig();
    test_summary(ice_led_blue);

    // tests run inside of the test jig
    button_wait_press_release();
    run_test_in_jig();
    test_summary(ice_led_green);

    // endless loop allowing the user to program the board FPGA and
    // debug the pin chain
    gpio_init(CHAIN_IN_PIN);
    gpio_set_dir(CHAIN_IN_PIN, GPIO_OUT);
    fpga_pins_high_z(false);
    while (true) {
        gpio_put(CHAIN_IN_PIN, 1);
        ice_usb_sleep_ms(10);
        gpio_put(CHAIN_IN_PIN, 0);
        ice_usb_sleep_ms(10);
    }

    return 0;
}
