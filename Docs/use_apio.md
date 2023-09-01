---
title: Use APIO
layout: default
nav_order: 3
parent: Getting Started
---

# Use APIO

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

If the USB driver setup did not work, it is also possible to convert the `.bin` file to `.uf2` and use
the [usb drag and drop](https://pico-ice.tinyvision.ai/programming_the_fpga.html#using-a-drag-drop-or-file-copy-scheme)
method which does not require firmware installation on Windows.
