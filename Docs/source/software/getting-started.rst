Getting Started
===============
This is a guide for how to build application running on the RP2040 microcontroller.

The [pico-ice-sdk](https://github.com/tinyvision-ai-inc/pico-ice-sdk/) provides an API for communicating with the pico-ice hardware, also allowing to use the Raspberry Pi [pico-sdk](https://github.com/raspberrypi/pico-sdk/) directly.

Other names than ``pico_ice_firmware`` and ``firmware`` may be chosen.

``CMakeLists.txt``:

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

``pico_ice_sdk_import.cmake``: [download](https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice-sdk/main/cmake/pico_ice_sdk_import.cmake)

With these two files, this example will produce a ``firmware.uf2`` that can be loaded onto the RP2040 microcontroller:

.. code-block:: shell
   $ ls
   CMakeLists.txt  pico_ice_sdk_import.cmake  firmware.c
   $ mkdir build
   $ cd build
   $ cmake ..
   [...]
   $ make
   [...]

A firmware.uf2 should result, that can be loaded onto the pico-ice RP2040 flash.

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
      $ cmake ..
      $ sed -i '/new_delete.cpp/ d' _deps/pico-sdk-src/src/rp2_common/pico_standard_link/CMakeLists.txt
      $ cmake ..

