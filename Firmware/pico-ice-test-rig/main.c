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

#define FIRST_GPIO 2
#define GPIO_RESETn 27

bool g_result = true;

void pull_output(uint pin, bool state) {
    // Change state of SWDIO or SWCLK using pull-up and pull-down.
    int pulls = state ? PADS_BANK0_GPIO0_PUE_BITS : PADS_BANK0_GPIO0_PDE_BITS;
    hw_write_masked(&padsbank0_hw->io[pin], pulls, PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS);
}

void check_state(int pin, bool state, const char* message) {
    if (gpio_get(pin) != state) {
        puts(message);
        g_result = false;
    }
}

void check_connected(int input_pin, int output_pin) {
    bool result = true;
  
    gpio_set_dir(output_pin, GPIO_OUT);

    gpio_put(output_pin, false);
    sleep_ms(1);
    result = result && gpio_get(input_pin) == false;

    gpio_put(output_pin, true);
    sleep_ms(1);
    result = result && gpio_get(input_pin) == true;

    gpio_set_dir(output_pin, GPIO_IN);
  
    if (!result) {
        printf("Failed: RP2040 pin %d expected to connect to %d.\n", input_pin, output_pin);
        g_result = false;
    }
}

void check_not_connected(int input_pin, int output_pin) {
    bool result = true;
  
    sleep_ms(1);
    bool initial_state = gpio_get(input_pin);

    gpio_set_dir(output_pin, GPIO_OUT);
    
    gpio_put(output_pin, false);
    sleep_ms(1);
    result = result && gpio_get(input_pin) == initial_state;

    gpio_put(output_pin, true);
    sleep_ms(1);
    result = result && gpio_get(input_pin) == initial_state;
  
    gpio_set_dir(output_pin, GPIO_IN);
  
    if (!result) {
        printf("Failed: RP2040 pin %d expected to not connect to %d.\n", input_pin, output_pin);
        g_result = false;
    }
}

void factory_test_rp2040(void) {
    gpio_init_mask(0xFFFFFFFF << FIRST_GPIO);

    // /RESET should be initially pulled down, holding the FPGA in reset.
    // While in reset, FPGA IOs should be high impedance, weak pull-up.
    check_state(GPIO_RESETn, false, "/RESET not initially low");

    // Check that GPIOs are connected to themselves, verifying e.g. that they are not bridged to power nets.
    for (int i = FIRST_GPIO; i < 30; ++i) {
        check_connected(i, i);
    }

    // Check adjacent GPIOs are not bridged.
    for (int i = FIRST_GPIO; i < 29; ++i) {
        check_not_connected(i, i+1);
    }

    // Check certain non-adjacent GPIOs are connected via pogo pins
    // TODO

    if (g_result) {
        printf("All RP2040 tests passed.\n");
    }
}

void factory_test_ice40(void) {
    ;
}


int main(void) {
    stdio_init_all();
    tusb_init();
    ice_fpga_init(48);
    ice_fpga_start();

    factory_test_rp2040();

    while (1) {
        tud_task();
    }

    return 0;
}
