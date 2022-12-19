---
title: ice_fpga.h
layout: default
parent: pico-ice-sdk
---

# `ice_fpga.h`

Low-level API for interacting with the FPGA chip.


## `void ice_fpga_init_clock(uint8_t frequency_mhz)`

`frequency_mhz` - Exported clock frequency in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.

The RP2040 exorts its own crystal-based clock to the iCE40, through the dedicated [`CLOCK GPOUT0`](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) feature.

This function is called by `ice_fpga_init()`.


## `void ice_fpga_init_uart(uint baudrate_hz)`

`baudrate_hz` - The baud rate speed in Hz.
Can be any value supported by the
[pico-sdk](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__uart.html).

Initialise the UART peripheral for communication with the FPGA ([pinout](../hardware/pinout.html)).

This function is called by `ice_fpga_init()`.


## `void ice_fpga_init(void)`

Initialise the FPGA chip and communication with it.
This will start the FPGA clock and take it out of reset.

This function is called by [`ice_sdk_init()`](ice_sdk.html).


## `bool ice_fpga_reset(void)`

Send a reset pulse to the FPGA re-reading its configuration then re-starting.
It must be called before ice_flash_init();

It will wait that the configuration is finished, once the FPGA sets CDONE high.


## `void ice_fpga_halt(void)`

Hold the FPGA in reset mode until ice_fpga_reset() is called.
Useful for programming the flash chip without disturbing the FPGA.
