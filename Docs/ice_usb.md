---
title: ice_usb.h
layout: default
parent: pico-ice-sdk
---

# `ice_usb.h`

The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/) makes use of
the [pico-sdk](https://github.com/raspberrypi/pico-sdk/) which uses
the [TinyUSB](https://github.com/hathach/tinyusb) library.

The pico-ice-sdk has a separate library for usb: `pico_ice_usb`, which only implements selected TinyUSB callbacks,
The library user needs to implement `tusb_config.h` and `usb_descriptors.c`.

* Callbacks for general USB configuration provide default behavior expected by most users
  (pull requests welcome for adjusting that behavior).
* Callbacks for DFU permit to program the FPGA through the CRAM (alt0) or flash (alt1) with i.e
[dfu-util](https://dfu-util.sourceforge.net/).
* Callbacks for CDC are small wrapper for dispatching individual CDC channels to individual functions.
* Callbacks for other devices classes are unoccupied.

Normal TinyUSB functions such as`tusb_init()` or `tud_task()` are to be called directly.

---

## `void (*tud_cdc_rx_cb_table[CFG_TUD_CDC])(uint8_t cdc_num)`

* `cdc_num` - this will be filled with the CDC interface receiving the message.

Table of CDC interface callbacks, that can be filled freely as long as tud_task() is not being executed.

The function would be called whenever tud_cdc_rx_cb() is executed,
and the position in the table indicates the CDC number at which that table entry would be called.

---

## `void ice_usb_cdc_to_uart0(uint8_t cdc_num)`
## `void ice_usb_cdc_to_uart1(uint8_t cdc_num)`

* `cdc_num` - The CDC interface number that the data was received from.

Read one byte from the indicated CDC interface and write it to the indicated UART interface.

These can be used in combination with `tud_cdc_rx_cb_table[]`
to pipe all data coming from an USB CDC interface to a physical UART interface.

---

## `void ice_usb_uart0_to_cdc0(void)`
## `void ice_usb_uart0_to_cdc1(void)`
## `void ice_usb_uart1_to_cdc0(void)`
## `void ice_usb_uart1_to_cdc1(void)`

Read one byte from the indicated UART interface and write it to the indicated CDC interface.

These can be used in combination with
[`irq_set_exclusive_handler()`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__irq.html#gafffd448ba2d2eef5b355b88180aefe7f)
to pipe all data coming from an USB CDC interface to a physical UART interface.
