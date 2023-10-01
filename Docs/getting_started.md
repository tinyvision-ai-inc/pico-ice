---
title: Getting Started
layout: default
nav_order: 1
parent: pico-ice
---

# Getting Started

Once you receive the board, you would be able to plug via USB and see the RGB LED blinking.
You might want to update the default firmware to make sure to have the latest bugfixes:


## Default Firmware

[source](https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Firmware/pico-ice-default/) -
[download](https://github.com/tinyvision-ai-inc/pico-ice/releases/)

To provide the various USB programming methods and allow to boot the FPGA, a
default firmware is loaded onto the RP2040 (Pico part of the pico-ice).

It provides:

- A first USB-UART (#0) is used for the and a REPL command line interface
  for now only showing help message and version information.

- A second USB-UART (#1) is used for mirroring everything between
  this USB interface UART TX on RP0 with ICE27, UART RX on RP1 with ICE25.

- A third USB-UART (#2) is exchanging data with the main SPI bus onboard
  ([doc](https://pico-ice.tinyvision.ai/ice_usb.html#usb-spi-fpgasramflash-forwarding)).

- A 12 MHz clock is exported from the RP2040 pin 24 toward the iCE40 pin 35.

- An USB DFU interface allows programming through [dfu-utils](https://dfu-util.sourceforge.net/)
  as shipped with [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build).

- An USB MSC interface allows programming the board by copying a file to an USB device
  ([doc](https://pico-ice.tinyvision.ai/programming_the_fpga.html#using-a-drag-drop-or-file-copy-scheme)).

See [Programing the MCU](/programming_the_mcu.html) for how to load this firmware file.


## Soldering the Pmods

In case you ordered the board without the [Pmod](/pmods.html) connectors soldered,
you would need to solder them in to plug something onto the board.
For instance like this:

![pmod install after soldering](images/pico_ice_pmod_install.jpg)
