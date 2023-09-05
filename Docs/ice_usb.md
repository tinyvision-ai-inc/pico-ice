---
title: ice_usb.h
layout: default
parent: pico-ice-sdk
---

# `ice_usb.h`

The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/) makes use of
the [pico-sdk](https://github.com/raspberrypi/pico-sdk/) which uses
the [TinyUSB](https://github.com/hathach/tinyusb) library for providing USB device mode and host mode.

`ice_usb` comes as a separate `pico_ice_usb` library to [add in the `CMakeLists.txt`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/develop/examples/pico_usb_uart/CMakeLists.txt#L21).

The library user needs to provide `tusb_config.h` and `usb_descriptors.c`.
Examples listed [below](#examples).
`tud_task()` needs to be called frequently in the firmware.


## USB CDC: UART forwarding

The pico-ice-sdk allows to configure forwarding from an USB CDC interface to an
UART interface with the two defines below:

To enable:
1. Define `ICE_USB_UART0_CDC` or `ICE_USB_UART1_CDC` to the CDC interface number to use.
2. Adjust these as needed:
   [`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
   [`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L30),
   [`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/tusb_config.h#L44),
   [`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L38),
   [`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_uart/usb_descriptors.c#L49)

See the
[`pico_usb_uart`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uart/)
example.


## USB SPI: FPGA/SRAM/flash forwarding

The pico-ice-sdk allows to configure forwarding data between an USB CDC interface and the main SPI interface around which everything is hooked-up together.
This allows to exchange data with the iCE40, SRAM and flash directly from USB.
To do so, a very small protocol was added on op of USB-CDC to control SPI:

When wanting to write `\x31\x32\x33\x34\x35` over SPI, the I/O over USB-CDC would be:
```
TX: -<0x05 0x31 0x32 0x33 0x34 0x35 0x00>-
RX: --------------------------------------
      WR*5   D1   D2   D3   D4   D5  END
```

When trying to read 4 bytes from SPI, the I/O over USB-CDC would be:
```
TX: -<0x84>-----------------------<0x00>-
RX: --------<0x00 0x00 0x00 0x00>--------
      RD*4    D1   D2   D3   D4    END
```

To change to a different SPI chip select pin, the I/O over USB-CDC would be:
```
TX: -<0x80 0x00>- or -<0x80 0x01>- or -<0x80 0x02>-
RX: -------------    -------------    -------------
      CMD  FPGA        CMD  SRAM        CMD  FLASH
```

You can use this python library:
[`pico_ice_spi.py`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/pico_ice_spi.py)

To enable:
1. Define `ICE_USB_SPI_CDC` to the CDC interface number to use.
2. Adjust these as needed:
   [`ITF_NUM_CDCx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L30),
   [`ITF_NUM_DATAx`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L30),
   [`CFG_TUD_CDC`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/tusb_config.h#L44),
   [`TUD_CDC_DESCRIPTOR`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L38),
   [`STRID_CDC+x`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/pico_usb_spi/usb_descriptors.c#L49)

See the
[`pico_usb_spi`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_spi/)
example.


## USB CDC: FPGA forwarding

The pico-ice-sdk allows to configure forwarding
from the USB CDC interface using the
[wishbone-serial](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge) protocol
to the FPGA SPI interface using the
[wishbone-spi](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#spi-bridge) protocol..

To enable:
1. Define `ICE_USB_FPGA_CDC` to the CDC interface number to use.
2. Adjust these as needed:
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

To enable:
1. Define `ICE_USB_USE_TINYUF2_MSC`
2. Adjust these as needed:
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

## `#define ICE_USB_FPGA_CDC`

The USB CDC interface number (0, 1, 2...) to use.
[wishbone-serial](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#serial-bridge)
requests sent to that interface will be sent as
[wishbone-spi](https://wishbone-utils.readthedocs.io/en/latest/wishbone-tool/#spi-bridge)
requests to the FPGA.

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

- [more...](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples)

## Troubleshooting

### Error: undefined reference to `tud_msc_read10_cb'

If the linker complains that TinyUSB library callbacks are missing, it is possible that
you still have USB devcie classes turned on in `tusb_config.h` that you do not use in
`usb_descriptors.c` (inside `tud_desc_configuration[]`).

You may check the configuration constants such as `CFG_TUD_MSC` and set them to 0 if
you do not use that feature.

If you do plan to use that feature, you might lack either the `ice_sdk_usb` or `tinyuf2`
who provide the TinyUSB callbacks.
