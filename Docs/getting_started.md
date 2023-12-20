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

See [Programing the MCU](md_programming__the__mcu.html) for how to load this firmware file.


## Soldering the Pmods

In case you ordered the board without the [Pmod](md_pmods.html) connectors soldered,
you would need to solder them in to plug something onto the board.
For instance like this:

![pmod install after soldering](images/pico_ice_pmod_install.jpg)


## Using the SDK

The [RP2040](https://www.raspberrypi.com/products/rp2040/specifications/) on the
pico-ice can be programmed with either custom C firmware, or languages such as
[MicroPython](https://micropython.org/download/RPI_PICO/),
[CircuitPython](https://circuitpython.org/board/raspberry_pi_pico/),
[Go](https://tinygo.org/docs/reference/microcontrollers/pico/),
[Rust](https://docs.rs/rp2040/latest/rp2040/),
[JavaScript](https://kalumajs.org/),
[ZeptoForth](https://github.com/tabemann/zeptoforth),
[Mecrisp Forth](https://wellys.com/posts/rp2040_forth/),
...

Currently C/C++ programming is best suported through the pico-ice-sdk:
a Raspberry Pi [pico-sdk](https://github.com/raspberrypi/pico-sdk/) library.

This is a guide for how to build application running on the RP2040 microcontroller.

The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/) provides an API for communicating with the pico-ice hardware, also allowing to use the Raspberry Pi [pico-sdk](https://github.com/raspberrypi/pico-sdk/) directly.

The pico-ice-sdk is organised as a normal pico-sdk project with `pico_ice` custom board.

The [examples](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/examples/) show how everything can be to get started.

Here is how to turn an example into a new project:

```bash
# copy the whole example directory
cp -r pico-ice-sdk/examples/pico_usb_uart my-new-pico-ice-firmware
cd my-new-pico-ice-firmware

# turn it into a git repository
git init
git remote add origin git@github.com:your-username/my-new-pico-ice-firmware

# replace the two symlinks by git submodules
rm pico-sdk pico-ice-sdk
git submodule add https://github.com/raspberrypi/pico-sdk
git submodule add https://github.com/tinyvision-ai-inc/pico-ice-sdk

# fetch the submodules (using --recursive is very slow)
git -C pico-ice-sdk submodule update --init
git -C pico-sdk submodule update --init lib/tinyusb

# you can now build it as a CMake project
mkdir build && cd build
cmake .. && make
```

You can now edit the name of the project in the CMakeLists.txt, add new sources, and change the code.


## Troubleshooting

Feel free to join the [chat server](https://discord.gg/sb2kwc66) to ask for help.


### Using some RP2040 peripheral cause various bugs.

In order to power the FPGA, some peripherals and GPIO pins are in use by the pico-ice-sdk.
In case both the firmware and SDK use the same peripheral, it is possible to use another free peripheral instance, or if none left, disable the feature of the SDK
The `ice_init()` is responsible for setting-up all peripherals used by the SDK.
Instead, calling manually each `ice_init_<feature>()` of interest permits to select what to enable or not in the board, and therefore keeping some more peripherals for the user.


### Error: C++ compiler not installed on this system

The pico-sdk is written in C, but uses a single C++ file to enable C++ support in the SDK.
This means you need a working C++ cross compiler, often named `arm-none-eabi-g++`.

Even if this binary is present in your system, it might not be a full C++ installation.
If you do not need C++ and want to work around this bug, you can disable the C++ support
in the pico-sdk. From your project repo:

```shell
$ cd build
$ cmake .. # download the SDK if not yet done
$ sed -i '/new_delete.cpp/ d' _deps/pico-sdk-src/src/rp2_common/pico_standard_link/CMakeLists.txt
$ cmake .. # rebuild the Makefile with the fix
```
