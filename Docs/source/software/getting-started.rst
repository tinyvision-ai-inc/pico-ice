Getting Started
===============
This is a guide for how to build application running on the RP2040 microcontroller.

The `pico-ice-sdk <https://github.com/tinyvision-ai-inc/pico-ice-sdk/>`_ provides an API for communicating with the pico-ice hardware, also allowing to use the Raspberry Pi `pico-sdk <https://github.com/raspberrypi/pico-sdk/>`_ directly.


CMake setup
-----------

``pico_ice_sdk_import.cmake``

   `download`_

   It clones both the pico-sdk and pico-ice-sdk, replacing Raspberry Pi's ``pico_sdk_import.cmake``.

.. _download: https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice-sdk/main/cmake/pico_ice_sdk_import.cmake

``CMakeLists.txt``

   .. code-block:: cmake
    
      cmake_minimum_required(VERSION 3.13)
      
      ## CMake configuration of pico-sdk and pico-ice-sdk
      include(pico_ice_sdk_import.cmake)
      project(pico_ice_firmware)
      pico_sdk_init()
      
      # CMake configuration of the application
      add_executable(firmware firmware.c)
      target_link_libraries(firmware pico_ice_sdk pico_stdlib)
      pico_add_extra_outputs(firmware)

   Other names than ``pico_ice_firmware`` and ``firmware`` may be chosen.

It will produce a ``firmware.uf2`` out of ``firmware.c``:

.. code-block::

   $ ls
   CMakeLists.txt  pico_ice_sdk_import.cmake  firmware.c
   $ mkdir -p build
   $ cd build
   $ cmake ..
   [...]
   $ make
   [...]

This should produce a ``firmware.uf2``, that can be loaded onto the pico-ice RP2040 flash.


Using the SDK
-------------

The source files, as listed in ``add_executable()``, can use the pico-ice-sdk API documented here to communicate with the hardware of the pico-ice boad.
Or it can use the `pico-sdk API <https://raspberrypi.github.io/pico-sdk-doxygen/>`_ for using use the RP2040 features, as long as it does not clash with the pice-ice-sdk.

The headers in the ``pico-ice`` directory can be included to access the functions described in the C API.

For example, reading from flash:

.. code-block:: C

   #include "pico/stdlib.h"
   #include "pico/stdio.h"
   #include "pico_ice/ice.h"
   
   int
   main(void)
   {
       stdio_init_all();
       ice_init_defaults();
   
       for (;;) {
           // Application code here

           ice_usb_task();
       }
   
       return 0;
   }


Troubleshooting
---------------

``C++ compiler not installed on this system``
   The pico-sdk is written in C, but uses a single C++ file to enable C++ support in the SDK.
   This means you need a working C++ cross compiler, often named ``arm-none-eabi-g++``.

   Even if this binary is present in your system, it might not be a full C++ installation.
   If you do not need C++ and want to work around this bug, you can disable the C++ support
   in the pico-sdk. From your project repo:

   .. code-block:: shell

      $ cd build
      $ cmake .. # download the SDK if not yet done
      $ sed -i '/new_delete.cpp/ d' _deps/pico-sdk-src/src/rp2_common/pico_standard_link/CMakeLists.txt
      $ cmake .. # rebuild the Makefile with the fix

The GPIO LEDs do not turn on
   Unlike the Raspberry Pi Pico board, which has a green LED attached to the GPIO pin 25,
   the pico-ice has three LEDs attached to the GPIO pin 22 (red), pin 23 (green), pin 24 (blue)
   Moreover, the leds are "active-low", so you would need to turn their pin down for them to
   be turned on.

Using some RP2040 peripheral cause various bugs.
   In order to power the FPGA, some peripherals and GPIO pins are in use by the pico-ice-sdk.
   In case both the firmware and SDK use the same peripheral, it is possible to use another free peripheral, or if none left, disable the feature of the SDK
   The ``ice_init_all()`` is responsible for setting-up all peripherals used by the SDK.
   Instead, calling manually each ``ice_init_<feature>()`` of interest permits to select what to enable or not in the board, and therefore keeping some more peripherals for the user.

Flashing an UF2 file does not change the memory neither restart the board
   The UF2 file format contains the destination addresses of each block.
   In case you used other tools than those provided,
   it is possible that that the addresses were outside the valid range of the flash chip.
   Try to copy the CURRENT.UF2 to NEW.UF2 upon that same directory, and unmount the device.
   This should trigger a restart of the device.
   This restart device should appear from the debug UART: ``board_dfu_complete: rebooting``.
