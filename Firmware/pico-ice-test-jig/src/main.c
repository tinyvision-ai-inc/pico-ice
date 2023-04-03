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

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_fpga.h"
#include "ice_led.h"

#define MIRRORED_BUTTON_PIN ICE_FPGA_27_PIN

static bool g_step_failed;
static bool g_test_failed;
static bool g_any_failed;

enum {
    TYPE_FREE_PIN = 0,
    TYPE_FPGA_PIN,
    PIN_TYPE_SPI,
    TYPE_LED_PIN,
} pin_type[] = {
    [0] = TYPE_FPGA_PIN,
    [1] = TYPE_FPGA_PIN,
    [2] = TYPE_FPGA_PIN,
    [3] = TYPE_FPGA_PIN,
    [4] = TYPE_FPGA_PIN,
    [5] = TYPE_FPGA_PIN,
    [6] = TYPE_FPGA_PIN,
    [7] = TYPE_FPGA_PIN,
    [8] = PIN_TYPE_SPI,
    [9] = PIN_TYPE_SPI,
    [10] = PIN_TYPE_SPI,
    [11] = PIN_TYPE_SPI,
    [12] = TYPE_LED_PIN,
    [13] = TYPE_LED_PIN,
    [14] = PIN_TYPE_SPI,
    [15] = TYPE_LED_PIN,
    [16] = TYPE_FREE_PIN,
    [17] = TYPE_FREE_PIN,
    [18] = TYPE_FREE_PIN,
    [19] = TYPE_FREE_PIN,
    [20] = TYPE_FREE_PIN,
    [21] = TYPE_FREE_PIN,
    [22] = TYPE_FREE_PIN,
    [23] = TYPE_FREE_PIN,
    [24] = TYPE_FPGA_PIN,
    [25] = TYPE_FREE_PIN,
    [26] = TYPE_FREE_PIN,
    [27] = TYPE_FREE_PIN,
    [28] = TYPE_FREE_PIN,
    [29] = TYPE_FREE_PIN,
};

/*
 *      GPIO26█───█GPIO15 (2i)
 *            :     │
 *      GPIO28█───█GPIO13
 *                : │
 *      GPIO29█───█GPIO12
 *          ┌─:─────┤
 *      GPIO16█───█GPIO20
 *          │     : │
 *      GPIO17█───█GPIO21
 *          │ :     │
 *      GPIO18█───█GPIO22
 *          │     : │
 * (2o) GPIO19█───█GPIO23
 *          │       │
 */
struct { uint8_t from, to; } pin_mirror[] = {
    { 21, 19 }, // 2o (in)
    { 23, 22 },
    { 18, 21 },
    { 16, 29 },
    { 12, 13 },
    { 28, 26 },
    { 15, 20 }, // 2i (out)
};

/*
 *          ┌───────┤
 * (0o) ICE_27█   █ICE_26 (0i)
 *          │       │
 * (1o) ICE_25█   █ICE_23 (1i)
 *          │       │
 * (2o) ICE_21█   █ICE_20 (2i)
 *          │       │
 * (3o) ICE_19█   █ICE_18 (3i)
 *          │       │
 */
const struct { uint8_t a, b; } pin_chain_ctl[] {
    [0] = { ICE_FPGA_27_PIN, ICE_FPGA_26_PIN },
    [1] = { ICE_FPGA_25_PIN, ICE_FPGA_23_PIN },
    [2] = { ICE_FPGA_21_PIN, ICE_FPGA_20_PIN },
    [3] = { ICE_FPGA_19_PIN, ICE_FPGA_18_PIN },
} ;

static void test_sleep_ms(uint32_t delay_ms) {
    for (uint32_t i = 0; i < delay_ms; i += 1) {
        tud_task();
        sleep_ms(1);
    }
}

static void test_assert(bool exp) {
    if (!exp) {
        g_step_failed = true;
        g_test_failed = true;
        g_any_failed = true;
    }
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
        printf("\nAll tests passed\n");
    }
}

static bool pull_output(uint pin, bool state) {
    // Change state of SWDIO or SWCLK using pull-up and pull-down.
    int pulls = state ? PADS_BANK0_GPIO0_PUE_BITS : PADS_BANK0_GPIO0_PDE_BITS;
    hw_write_masked(&padsbank0_hw->io[pin], pulls, PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS);
}

static bool check_pin_state(int pin, bool state) {
    g_step_failed = false;
    test_assert(gpio_get(pin) == state);
    if (g_step_failed) {
        printf(" FAIL - %s(%d, %s)\n", __func__, pin, state ? "true" : "false");
    }
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

    if (g_step_failed) {
        printf(" FAIL - %s(%d, %d)\n", __func__, input_pin, output_pin);
    }
}

static void check_free_pin_not_connected(int input_pin, int output_pin) {
    g_step_failed = false;
    gpio_set_dir(input_pin, GPIO_IN);
    gpio_set_dir(output_pin, GPIO_OUT);
    gpio_set_pulls(input_pin, true, false); // pull-up

    for (int i = 0; i < 10; i++) {
        gpio_put(output_pin, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);

        gpio_put(output_pin, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);
    }

    if (g_step_failed) {
        printf(" FAIL - %s(%d, %d)\n", __func__, input_pin, output_pin);
    }
}

static void check_fpga_pin_not_connected(int input_pin, int output_pin) {
    g_step_failed = false;
    gpio_set_dir(input_pin, GPIO_IN);
    gpio_set_dir(output_pin, GPIO_OUT);
    gpio_set_pulls(input_pin, true, false); // pull-up

    for (int i = 0; i < 10; i++) {
        gpio_put(output_pin, 0);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);

        gpio_put(output_pin, 1);
        test_sleep_ms(1);
        test_assert(gpio_get(input_pin) == 1);
    }

    if (g_step_failed) {
        printf(" FAIL - %s(%d, %d)\n", __func__, input_pin, output_pin);
    }
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

    if (g_step_failed) {
        printf(" FAIL - %s(%d)\n", __func__, pin);
    }
}

static void check_fpga_pin_consistent(int pin) {
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

    if (g_step_failed) {
        printf(" FAIL - %s(%d)\n", __func__, pin);
    }
}

static void run_rp2040_tests(void) {

    // RP2040 tests

    ice_fpga_stop();

    // CRESET_B_PIN should be initially pulled down, holding the FPGA in reset.
    // While in reset, FPGA IOs should be high impedance, weak pull-up.
    test_start("RP2040 pin CRESET_B");
    check_pin_state(ICE_FPGA_CRESET_B_PIN, false);
    test_end();

    // Check that GPIOs are connected to themselves, verifying e.g. that they are not bridged to power nets.
    test_start("RP2040 pin self-test");
    ice_fpga_start();
    for (int i = FIRST_GPIO; i <= LAST_GPIO; ++i) {
        switch (pin_type[i]) {
        case TYPE_FREE_PIN:
            check_free_pin_consistent(i);
            break;
        case TYPE_FPGA_PIN:
            check_fpga_pin_consistent(i);
            break;
        case TYPE_LED_PIN:
            break;
        }
    }
    ice_fpga_stop();
    test_end();

#define TYPE_PAIR(t1, t2) (((t1) << 8) & 0xFF | ((t2) << 0) & 0xFF)

    // Check adjacent GPIOs are not bridged.
    test_start("RP2040 pin not bridged");
    for (int i = FIRST_GPIO; i <= LAST_GPIO - 1; ++i) {
        switch (TYPE_PAIR(pin_type[i], pin_type[i + 1])) {
        case TYPE_PAIR(TYPE_FREE_PIN, TYPE_FREE_PIN):
            check_free_pin_not_connected(i, i + 1);
            break;
        case TYPE_PAIR(TYPE_FPGA_PIN, TYPE_FPGA_PIN):
            check_fpga_pin_not_connected(i, i + 1);
            break;
        default:
            break;
        }
    }
    test_end();

    // Check certain non-adjacent GPIOs are connected via pogo pins
    // TODO
    test_start("RP2040 pin connected");
    //check_pin_connected(x1, x2);
    test_end();
}

static void run_ice40_tests(void) {
    ice_fpga_init(48);
    ice_fpga_start();

    test_start("iCE40 pin chain");
    test_end();
}

static bool button_pressed(void) {
    test_sleep_ms(1);
    return gpio_get(ICE_BUTTON_PIN);
}

int main(void) {
    stdio_init_all();
    tusb_init();
    ice_led_init();

    gpio_init(ICE_BUTTON_PIN);

    // wait that the button gets pressed a first time
    while (!button_pressed()) {
        tud_task();
        printf("button still not pressed... ");
    }

    // expected to run tests outside of the test jig
    run_rp2040_tests();
    test_summary(ice_led_blue);

    // wait that the button gets pressed a second time
    while (!button_pressed()) {
        tud_task();
    }

    // expected to run tests inside of the test jig
    run_ice40_tests();
    test_summary(ice_led_blue);

    // Allow the user to program the board FPGA
    while (1) {
        tud_task();
    }

    return 0;
}
