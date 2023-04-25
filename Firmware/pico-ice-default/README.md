# Default firmware for the pico-ice

This firmware is a minimal starting point that is programmed onto the
device at factory time.

It permits to program the FPGA chip through either:

- USB-DFU (RAM or flash), using the `dfu-util` tool.

- USB-MSC (flash): a `pico-ice` storage device should appear.
  Copy a `.uf2` on it and eject it.
