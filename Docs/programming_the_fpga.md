---
title: Programming the FPGA
layout: default
nav_order: 1
parent: pico-ice
---

# Programming the iCE40 FPGA

1. Get a pico-ice with the [`pico-empty`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/example/pico-empty) example [loaded onto the RP2040](programming_the_mcu.html).

2. Install or build the [UF2 Tools](uf2_tools.html),
and a [blinky example](https://github.com/tinyvision-ai-inc/UPduino-v3.0/blob/master/RTL/blink_led/rgb_blink.bin) for any iCE40 board.
 
3. Convert the binary bitstream `rgb_blink.bin` into an UF2 `rgb_blink.uf2` with the UF2 Tools:
```shell
$ bin2uf2 -o rgb_blink.uf2 rgb_blink.bin
```

4. Connect the pico-ice via USB and lookup the USB drive named `pico-ice`. Open it.

5. You can copy the `rgb_blink.uf2` file to that drive you just attached. As soon as you eject/unmount the drive, the bitstream file will be programmed onto the FPGA flash.

There is a bug being worked on for allowing the bitstream to be effective right after reboot.
For now, it is holding the FPGA in reset.
