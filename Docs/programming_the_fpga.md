---
title: Programming the FPGA
layout: default
nav_order: 2
parent: pico-ice
---

# Programming the iCE40 FPGA

The FPGA normally boots from a dedicated serial NOR flash.
This flash can be programmed by the Pico processor which exposes the flash to the host OS as either a removable drive or a DFU endpoint.

On Windows, while the RaspberryPi guide mentions using Visual Studio Code with a plugin a an IDE, better results were obtained by using the [WSL2 environment](https://learn.microsoft.com/en-us/windows/wsl/install).

## Using a Drag-Drop or file copy scheme

You would need a compiler toolchain installed for building the [UF2 Utils](https://github.com/tinyvision-ai-inc/uf2-utils) on your system.
On Windows, you can use <https://github.com/microsoft/uf2> instead,
which contains [uf2conv.py](https://github.com/microsoft/uf2/blob/master/utils/uf2conv.md).

Out of the box, the [default firmware](https://github.com/tinyvision-ai-inc/pico-ice/releases/) should already be present on your board.
You can skip step 1 if this is the case.

1.  If you changed the default firwmare, [program](programming_the_mcu.html) it again onto the RP2040.
    You can also integrate the FPGA programming code in your own firmware with [ice_usb.h](/ice_usb.html).

2.  Install or build the [UF2 Utils](https://github.com/tinyvision-ai-inc/uf2-utils),
    and a [blinky example](https://github.com/tinyvision-ai-inc/UPduino-v3.0/blob/master/RTL/blink_led/rgb_blink.bin) for any iCE40 board.

3.  Convert the binary bitstream `rgb_blink.bin` into an UF2 `rgb_blink.uf2` with the UF2 Utils:

     ```shell
     $ bin2uf2 -o rgb_blink.uf2 rgb_blink.bin
     ```

4.  Connect the pico-ice via USB and lookup the USB drive named `pico-ice`. Open it.

5.  You can copy the `rgb_blink.uf2` file to that drive you just attached.
    As soon as you copy the file over,t he pico-ice will reboot and allow the FPGA to come up depending on the code running in the Pico processor.

## Using the DFU mode

1.  If you changed the default firwmare, [program](programming_the_mcu.html) it again onto the RP2040.
    You can also integrate the FPGA programming code in your own firmware with [ice_usb.h](/ice_usb.html).

2.  Install the DFU utilities.

    a.  For Windows, [yosys-hq tabby-cad](https://www.yosyshq.com/tabby-cad-datasheet):
        double-clicking on `start.bat` on the OSS CAD Suite installation opens a prompt with the dfu-util command available.

    b.  For other systems you can install the [dfu-util](https://repology.org/project/dfu-util/versions) package.

3.  Check whether the Pico is recognized as a DFU device: `dfu-util -l`.
    This should list the pico-ice as a DFU device:

    ```
    Found DFU: [1209:b1c0] ver=0100, devnum=105, cfg=1, intf=0, path="1-4.4", alt=1, name="iCE40 DFU (flash)", serial="DE62A435436F5939"
    Found DFU: [1209:b1c0] ver=0100, devnum=105, cfg=1, intf=0, path="1-4.4", alt=0, name="iCE40 DFU (CRAM)", serial="DE62A435436F5939"
    ```

4.  Download the FPGA bin file to the pico-ice.
    The Pico can be rebooted as soon as the download succeeds with the `-R` flag.

    ```
    $ dfu-util -a 1 -D rgb_blink.bin
    ```

## Troubleshooting

### Checking the CDONE pin

Once the FPGA bitfile transfers over using the DFU protocol,
the Pico will check for whether the DONE pin goes high indicating a successful boot.
This would make the CDONE green LED bright.

If this doesnt happen for whatever reason,
the DFU utility will throw an error indicating that this did not succeed.

### Booting the FPGA with custom firmware

The user writing a custom firmware with the pico-ice-sdk should take care of starting the FPGA from the MCU.
Review the [pico_fpga](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_fpga) example
for how this can be done, as well as the [`ice_fpga.h`](ice_fpga.html) library documentation.

The USB DFU provided as part of the pico-ice-sdk must also be enabled for the DFU interface to show-up.
The [pico_usb_uart example](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples/pico_usb_uart) project have it enabled by default.

### Cannot open DFU device 1209:b1c0 found on devnum 61 (LIBUSB_ERROR_NOT_FOUND)

This error might occur when a communication error occurs.

- On Windows operating system, the device needs to be declared with [Zadig](https://zadig.akeo.ie/) as described [here](https://github.com/pbatard/libwdi/wiki/Zadig#basic-usage).
  Make sure to select the pico-ice device on the list rather than any other to avoid erasing your system's USB drivers.

- On Linux operating system, it might need to be allowed with an udev rule,
  or `dfu-util` might need to be run as super user.

### dfu-util is stuck while uploading before anything could be sent

This could be due that there was no response from the flash chip, and the RP2040 is endlessy waiting the write confirmation.

If you had an earlier board, it could be due to the fact the TX and RX pins were swapped, and do not work for the old board anymore.

### Flashing an UF2 file does not change the memory neither restart the board

The UF2 file format contains the destination addresses of each block.
In case you used other tools than those provided,
it is possible that that the addresses were outside the valid range of the flash chip.
Try to copy the CURRENT.UF2 to NEW.UF2 upon that same directory, and unmount the device.
This should trigger a restart of the device.
This restart device should appear from the debug UART: `board_dfu_complete: rebooting`.

### Device's firmware is corrupt. It cannot return to run-time (non-DFU) operations.

This message sometimes comes from `dfu-util` when the `-R` flag is not used.
With the `-R` flag, the pico-ice will reboot at the end of the transfer,
and DFU-util should not complain anymore.
