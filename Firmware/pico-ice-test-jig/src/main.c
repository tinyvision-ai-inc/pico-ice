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

// pico-sdk
#include "pico/stdlib.h"
#include "pico/stdio.h"

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_led.h"

#define FIRST_GPIO  0
#define LAST_GPIO   29
#define FPGA_BUTTON_PIN     ICE_FPGA_20_PIN // Mirrored from the FPGA
#define FPGA_HIGH_Z_PIN     ICE_FPGA_21_PIN

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
    // shared PMOD pins
    [0]     = TYPE_FPGA_PIN,
    [1]     = TYPE_FPGA_PIN,
    [2]     = TYPE_FPGA_PIN,
    [3]     = TYPE_FPGA_PIN,
    [4]     = TYPE_FPGA_PIN,
    [5]     = TYPE_FPGA_PIN,
    [6]     = TYPE_FPGA_PIN,
    [7]     = TYPE_FPGA_PIN,

    // SPI bus
    [8]     = TYPE_SPI_PIN,
    [9]     = TYPE_SPI_PIN,
    [10]    = TYPE_SPI_PIN,
    [11]    = TYPE_SPI_PIN,
    [14]    = TYPE_SPI_PIN,

    // Boolean signal pins
    [ICE_LED_RED_PIN]       = TYPE_LED_PIN,
    [ICE_LED_GREEN_PIN]     = TYPE_LED_PIN,
    [ICE_LED_BLUE_PIN]      = TYPE_LED_PIN,
    [FPGA_BUTTON_PIN]       = TYPE_SYSTEM_PIN,
    [FPGA_HIGH_Z_PIN]       = TYPE_SYSTEM_PIN,
    [ICE_FPGA_CRESET_B_PIN] = TYPE_SYSTEM_PIN,
    [ICE_FPGA_CDONE_PIN]    = TYPE_SYSTEM_PIN,

    // FPGA clock pin
    [24]    = TYPE_FPGA_PIN,
};

/*
 *     └───────┤
 * GPIO26█───█GPIO15
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
const struct { uint8_t from, to; } pin_linked[] = {
    { 26, 15 },
    { 28, 13 },
    { 29, 12 },
    { 16, 20 },
    { 17, 21 },
    { 18, 22 },
    { 19, 23 },
};

/*
 *          ┌───────┤
 * (0o) ICE_25█   █ICE_23 (0i)
 *          │       │
 * (1o) ICE_19█   █ICE_18 (1i)
 *          │       │
 * (2o) ICE_27█   █ICE_26 (2i)
 *          │       │
 */
const struct { uint8_t o, i; } pin_chain[] = {
    [0] = { ICE_FPGA_25_PIN, ICE_FPGA_23_PIN },
    [1] = { ICE_FPGA_19_PIN, ICE_FPGA_18_PIN },
    [2] = { ICE_FPGA_27_PIN, ICE_FPGA_26_PIN },
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

static bool pin_is_pulled(uint8_t pin) {
    switch (pin_type[pin]) {
    case TYPE_SPI_PIN:
    case TYPE_LED_PIN:
    case TYPE_SYSTEM_PIN:
        return true;
    default:
        return false;
    }
}

static bool button_wait_press_release(void) {
    while (!button_pressed());
    while (button_pressed());
}

static bool fpga_pins_high_z(bool state) {
    gpio_set_dir(FPGA_HIGH_Z_PIN, GPIO_OUT);
    gpio_put(FPGA_HIGH_Z_PIN, state);
}

static bool check_pin_state(int pin, bool state) {
    g_step_failed = false;
    test_assert(gpio_get(pin) == state);
    test_step_printf("%s(%d, %s)", __func__, pin, state ? "true" : "false");
}

static void check_pin_connected(int input_pin, int output_pin) {
    g_step_failed = false;
    gpio_set_dir(output_pin, GPIO_OUT);
    gpio_set_dir(input_pin, GPIO_IN);
    gpio_disable_pulls(input_pin);

    for (int i = 0; i < 10; i++) {
        gpio_put(output_pin, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 0);

        gpio_put(output_pin, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);
    }

    test_step_printf("%s(%d, %d)", __func__, input_pin, output_pin);
}

static void check_pin_not_connected(int input_pin, int output_pin) {
    g_step_failed = false;
    gpio_set_dir(output_pin, GPIO_OUT);
    gpio_set_dir(input_pin, GPIO_IN);
    gpio_set_pulls(input_pin, true, false);

    for (int i = 0; i < 10; i++) {
        gpio_put(output_pin, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);

        gpio_put(output_pin, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);
    }

    test_step_printf("%s(%d, %d)", __func__, input_pin, output_pin);
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
}

static void run_out_of_jig_tests(void) {
    // check that GPIOs are connected to themselves, verifying e.g. that they are not bridged to power nets
    test_start("RP2040 pin self-test");
    for (int i = FIRST_GPIO; i <= LAST_GPIO; ++i) {
        switch (pin_type[i]) {
        case TYPE_FREE_PIN:
        case TYPE_FPGA_PIN:
            check_free_pin_consistent(i);
            break;
        case TYPE_LED_PIN:
        case TYPE_SPI_PIN:
            check_pulled_pin_consistent(i);
            break;
        case TYPE_SYSTEM_PIN:
            break;
        }
    }
    test_end();

    // check adjacent GPIOs are not bridged.
    test_start("RP2040 pin not bridged");
    for (int i = FIRST_GPIO, o = i + 1; o <= LAST_GPIO; i++, o++) {
        if (!pin_is_pulled(i) && pin_is_drivable(o)) {
            check_pin_not_connected(i, o);
        }
    }
    test_end();

    // check certain non-adjacent gpios are connected via pogo pins
    // TODO
    test_start("RP2040 pin connected");
    //check_pin_connected(x1, x2);
    test_end();
}

static void run_in_jig_tests(void) {
    test_start("iCE40 pin chain");
    test_end();
}

int main(void) {
    stdio_init_all();
    tusb_init();

    // initial state of all pins: input
    for (int i = 0; i <= LAST_GPIO; i++) {
        gpio_init(i);
    }

    // initialize the peripheral after the great cleanup above
    ice_led_init();
    ice_fpga_init(48);
    ice_fpga_start();

    // run the FPGA from internal oscillator
    gpio_init(ICE_FPGA_CLOCK_PIN);

    // tests run outside of the test jig
    fpga_pins_high_z(true);
    button_wait_press_release();
    run_out_of_jig_tests();
    test_summary(ice_led_blue);

    // tests run inside of the test jig
    fpga_pins_high_z(false);
    button_wait_press_release();
    run_ice40_tests();
    test_summary(ice_led_blue);

    // endless loop allowing the user to program the board FPGA
    while (1) {
        tud_task();
    }

    return 0;
}
