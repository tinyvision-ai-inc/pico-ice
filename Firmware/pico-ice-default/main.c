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

#include "pico/stdio.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "ice_usb.h"
#include "ice_fpga.h"

int main(void) {
    stdio_init_all(); // uses CDC0, next available is CDC1
    tusb_init();

    // Let the FPGA start and give it a clock
    ice_fpga_init(48);
    ice_fpga_start();

    // Enable the UART
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    // Bind USB CDC1 callback for piping input data to UART0
    tud_cdc_rx_cb_table[1] = &ice_usb_cdc_to_uart0;

    // Bind UART0 interrupt for piping to USB CDC1
    irq_set_exclusive_handler(UART0_IRQ, ice_usb_uart0_to_cdc1);

    while (true) {
        tud_task();
    }
    return 0;
}
