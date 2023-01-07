---
title: Programming the FPGA
layout: default
nav_order: 1
parent: pico-ice
---

# Programming the iCE40 FPGA
The FPGA normally boots from a dedicated serial NOR flash. This Flash can be programmed by the Pico processor which exposes the Flash to the host OS as either a removable drive or a DFU endpoint.

## Using a Drag-Drop or file copy scheme

1. Get a pico-ice with the [`pico-empty`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/example/pico-empty) example [loaded onto the RP2040](programming_the_mcu.html).

2. Install or build the [UF2 Tools](uf2_tools.html),
and a [blinky example](https://github.com/tinyvision-ai-inc/UPduino-v3.0/blob/master/RTL/blink_led/rgb_blink.bin) for any iCE40 board.

3. Convert the binary bitstream `rgb_blink.bin` into an UF2 `rgb_blink.uf2` with the UF2 Tools:

    ```shell
    $ bin2uf2 -o rgb_blink.uf2 rgb_blink.bin
    ```

4. Connect the pico-ice via USB and lookup the USB drive named `pico-ice`. Open it.

5. You can copy the `rgb_blink.uf2` file to that drive you just attached. As soon as you copy the file over,t he pico-ice will reboot and allow the FPGA to come up depending on the code running in the Pico processor.

## Using the DFU mode

1. Follow the same step as above for building the `pico-empty` code.

2. Install the DFU utilities, preferably from the [`yosys-hq`](https://www.yosyshq.com/tabby-cad-datasheet) site. This version is known to work on Windows.

    a. If using Windows, you can open a OSS prompt by double clicking on the `start.bat` file in the OSS CAD Suite installation.

3. Check whether the Pico is recognized as a DFU device: `dfu-util -l`. This should list the pico-ice as a DFU device:

    ```shell
    $ dfu-util -l
    dfu-util 0.11-dev

    Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
    Copyright 2010-2021 Tormod Volden and Stefan Schmidt
    This program is Free Software and has ABSOLUTELY NO WARRANTY
    Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

    Found DFU: [1209:0001] ver=0100, devnum=5, cfg=1, intf=5, path="2-2.3", alt=0, name="DFU flash", serial="DE622480A7482A2A"
    ```

4. Download the FPGA bin file to the pico-ice. The Pico can be rebooted as soon as the download succeeds by passing the optional `-R` argument to the `dfu-utl` program.

    ```shell
    $ dfu-util -D rgb_blink.bin
    dfu-util 0.11-dev

    Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
    Copyright 2010-2021 Tormod Volden and Stefan Schmidt
    This program is Free Software and has ABSOLUTELY NO WARRANTY
    Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

    Opening DFU capable USB device...
    Device ID 1209:0001
    Run-Time device DFU version 0101
    Claiming USB DFU Interface...
    Setting Alternate Interface #0 ...
    Determining device status...
    DFU state(2) = dfuIDLE, status(0) = No error condition is present
    DFU mode device DFU version 0101
    Device returned transfer size 256
    Copying data from PC to DFU device
    Download        [=========================] 100%       104090 bytes
    Download done.
    DFU state(7) = dfuMANIFEST, status(0) = No error condition is present
    DFU state(8) = dfuMANIFEST-WAIT-RESET, status(0) = No error condition is present
    Resetting USB to switch back to runtime mode
    Done!
    Warning: Invalid DFU suffix signature
    A valid DFU suffix will be required in a future dfu-util release
    ```

Notes:

1. Once the FPGA bitfile transfers over using the DFU protocol, the Pico will check for whether the DONE pin goes high indicating a successful boot. If this doesnt happen for whatever reason, the DFU utility will throw an error indicating that this did not succeed.

    ```
    DFU state(10) = dfuERROR, status(10) = Device's firmware is corrupt. It cannot return to run-time (non-DFU) operations
    ```
