---
title: ice_usb.h
layout: default
parent: pico-ice-sdk
---

# `ice_usb.h`

The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/) makes use of
the [pico-sdk](https://github.com/raspberrypi/pico-sdk/) which uses
the [TinyUSB](https://github.com/hathach/tinyusb) library.

It comes as a separate library to link against the target: `pico_ice_usb`.

The library user needs to implement short `tusb_config.h` and `usb_descriptors.c` himself.
Examples listed [at the bottom](#examples).

`tud_task()` from TinyUSB still need to be called periodically.

## USB CDC: UART forwarding

The pico-ice-sdk allows to configure forwarding from an USB CDC interface to an
UART interface with the two defines below:

Dependencies: `ICE_USB_USE_DEFAULT_CDC`, `ICE_USB_UART_CDC`, `ICE_USB_UART_NUM`
[`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
[`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
[`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L44),
[`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L38),
[`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L49)

See the
[`pico_usb_uart`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uart/)
example.

## USB CDC: FPGA forwarding

The pico-ice-sdk allows to configure forwarding
from the USB CDC interface using the
[wishbone-serial](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge) protocol
to the FPGA SPI interface using the
[wishbone-spi](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#spi-bridge) protocol..

Dependencies: `ICE_USB_USE_DEFAULT_CDC`, `ICE_USB_FPGA_CDC`,
[`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
[`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
[`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L44),
[`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L38),
[`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L49)

See the
[`pico_usb_fpga`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_fpga/)
example.

## USB MSC: [TinyUF2](https://github.com/adafruit/tinyuf2)

The TinyUF2 library from Adafruit permits to expose an MSC USB storage device, with a fake FAT filesystem.
This will allow to copy UF2-formatted files using a drag-and-drop scheme containing a bitstream programmed into the FPGA flash.
This means no Zadig driver setup needed on Windows.

You would need something like the [`uf2-utils`](https://github.com/tinyvision-ai-inc/uf2-utils) to generate the UF2-formatted files.

Dependencies: `ICE_USB_USE_TINYUF2_MSC`, `ICE_USB_FPGA_CDC`,
[`ITF_NUM_MSCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
[`CFG_TUD_MSC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L45),
[`TUD_MSC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uf2/usb_descriptors.c#L37),
[`STRID_MSC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uf2/usb_descriptors.c#L49)

See the
[`pico_usb_uf2`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uf2/)
example.

---

## `#define ICE_USB_USE_DEFAULT_DFU`

If set to non-zero, provides an implementation for TinyUSB DFU callbacks.
Callbacks for DFU permit to program the FPGA through the CRAM (alt0) or flash (alt1) with i.e
[dfu-util](https://dfu-util.sourceforge.net/).

---

## `#define ICE_USB_USE_TINYUF2_MSC`

If set to non-zero, provides an implementation for TinyUSB MSC callbacks.
These permits to enable an extra UF2 drive for loading the FPGA bitstream to them.

---

## `#define ICE_USB_USE_DEFAULT_CDC`

If set to non-zero, provides an implementation for TinyUSB CDC callbacks.
See `tud_cdc_rx_cb_table` below.

---

## `#define ICE_USB_UART_CDC`

The USB CDC interface number (0, 1, 2...) to use for USB-CDC <-> UART forwarding.
All data sent to this USB interface will be sent to the UART below.

---

## `#define ICE_USB_UART_NUM`

The UART interface number (0 or 1) to use for USB-CDC <-> UART forwarding.
All data sent ot this UART interface will be sent to the USB CDC above.

---

## `#define ICE_USB_FPGA_CDC` - the USB CDC interface number (0, 1, 2...) to use.
  wishbone-serial requests sent to that interface will be sent as
  wishbone-spi requests to the FPGA.
  This sets [`<ice_wishbone.h>`](/ice_wishbone.html) callbacks.

See the
[`pico_fpga_io`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_fpga_io/)
example.

---

## `void ice_usb_init(void)`

Initiates the CDC forwarding as well as the TinyUSB library.

If CDC forwarding is not used, you can initiate TinyUSB yourself by calling
`tud_init()` directly.

---

## `void ice_usb_sleep_ms(uint32_t ms)`

- `ms` to sleep in milliseconds, while calling `tud_task()` every millisecond.

This is a replacement for `sleep_ms()`, making USB stuck.
Shorter delays can use `sleep_us()` which does not get the appication stuck long enough to become a problem.

<https://forums.raspberrypi.com/viewtopic.php?t=333027>

---

## `void (*tud_cdc_rx_cb_table[CFG_TUD_CDC])(uint8_t byte)`

- `byte` - this will be filled with a byte read from the selected CDC interface.

A table for controlling how USB CDC interfaces are dispatched: upon reception
of a byte on a CDC interface `N`, the function in the table at position `N` is
called with that byte as argument.

This permits to catch the content sent to an USB CDC stream by adding a new
entry to that table.

It is only required to adjust it for custom CDC interfaces. The built-in ones
are already configured in that table by default.

---

## Examples

- [`pico_hello_world`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_hello_world/)

- [`pico_usb_uart`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_hello_world/)

- [`pico_usb_uf2`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_hello_world/)

- [`pico_usb_fpga`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_fpga_io/)

- [`pico_fpga_io`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_fpga_io/)

---

## Troubleshooting

### Error: undefined reference to `tud_msc_read10_cb'

If the linker complains that TinyUSB library callbacks are missing, it is possible that
you still have USB devcie classes turned on in `tusb_config.h` that you do not use in
`usb_descriptors.c` (inside `tud_desc_configuration[]`).

You may check the configuration constants such as `CFG_TUD_MSC` and set them to 0 if
you do not use that feature.

If you do plan to use that feature, you might lack either the `ice_sdk_usb` or `tinyuf2`
who provide the TinyUSB callbacks.
