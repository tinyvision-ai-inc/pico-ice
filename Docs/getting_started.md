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


## Quick-start with APIO

The [APIO](https://github.com/FPGAwars/apio) project is a command line tool to fetch and use
the [oss-cad-suite](https://github.com/YosysHQ/oss-cad-suite-build) FPGA toolchain based
on [Yosys](https://github.com/YosysHQ/).

It will bring an up-to-date build environment running quickly.

On Windows, you will first need to setup the `libusbK` driver for `pico-ice DFU (CRAM)`
[with Zadig](https://zadig.akeo.ie/) or [with UsbDriverTool](https://visualgdb.com/UsbDriverTool/)
([doc](https://github.com/FPGAwars/apio/wiki/Quick-start)).

```
# Download the latest APIO dev version (with pico-ice support):
pip3 install git+https://github.com/FPGAwars/apio

# Download and install oss-cad-suite
apio install -a

# Build a new directory with a "blinky" example project inside
mkdir pico-ice-blinky; cd pico-ice-blinky
apio examples -f iCE40-UP5K/blink

# Set the board to "pico-ice"
apio init --sayyes --board pico-ice

# Build the project using yosys/nextpnr
apio build

# Plug your pico-ice board and upload the blinky project to it
apio upload
```


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
