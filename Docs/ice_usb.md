---
title: ice_usb.h
layout: default
parent: pico-ice-sdk
---

# `ice_usb.h`

Library implementing support for the
[TinyUSB](https://github.com/hathach/tinyusb/) as well as
[TinyUF2](https://github.com/adafruit/tinyuf2/) stacks.

There is usually no need to interact with it directly.

Together, they provide the following **USB services**:

* An USB storage interface with a fake FAT filesystem,
  permitting one to upload FPGA code
  (see the [gateware](../gateware/) doc).
  This is MSC0.

* An USB UART interface bound to the pico-sdk stdin/stdout,
  handled by the native library
  [`pico_stdio_usb`](https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__stdio__usb.html).
  This is ACM0.

* An USB UART interface bound to two pins of the FPGA,
  permitting to implement an UART FPGA core accessible over USB
  (see the [pinout](../hardware/pinout.html) doc).
  This is ACM1.

---

## `void tud_task(void)`

Function from the TinyUSB library that must be called frequently so that the USB features remain available.

One common way to do it is by placing a call on the top of the main
program loop, as well as within every blocking function looping over a rare event.

For instance, reading user input with a timeout, calling `tud_task()` before trying to read user input again.

---

## `void ice_usb_init(void)`

Initialize the TinyUSB library, enabling the UART (CDC) and drag-and-drop (MSC) interfaces.

This function is called by [`ice_sdk_init()`](ice_sdk.html).
