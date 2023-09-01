---
title: Getting Started
layout: default
nav_order: 1
parent: pico-ice
---

# Getting Started

Once you receive the board, you would be able to plug via USB and see the RGB LED blinking.
You might want to [update your firmware](https://github.com/tinyvision-ai-inc/pico-ice/releases/) to make sure to have the latest bugfixes.

- Program a new FPGA design onto the iCE40: [programming the FPGA](/programming_the_fpga.html).

- Program a custom firmware onto the RP2040: [Programming the MCU](/programming_the_mcu.html).

- Use APIO to program the FPGA: [Use APIO](/use_apio.html).


## Default Firmware

[source](https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Firmware/pico-ice-default/) -
[download](https://github.com/tinyvision-ai-inc/pico-ice/releases/)

To provide the various USB programming methods and allow to boot the FPGA, a
default firmware is loaded onto the RP2040 (Pico part of the pico-ice).

It provides:

- USB programming with DFU
- USB programming with UF2 (drag-and-drop to a storage device)
- USB-UART forwarding


## Soldering the PMODs

In case you ordered the board without the Pmod connectors soldered,
you would need to solder them in to plug something onto the board.
For instance like this:

![pmod install after soldering](images/pico_ice_pmod_install.jpg)
