Getting Started
===============
This is a guide for how to build application running on the RP2040 microcontroller.

The `pico-ice-sdk <https://github.com/tinyvision-ai-inc/pico-ice-sdk/>`_ provides an API for communicating with the pico-ice hardware, also allowing to use the Raspberry Pi `pico-sdk <https://github.com/raspberrypi/pico-sdk/>`_ directly.


CMake setup
-----------

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

    It will produce a ``firmware.uf2`` out of ``firmware.c``.
    Other names than ``pico_ice_firmware`` and ``firmware`` may be chosen.

``pico_ice_sdk_import.cmake`` `download`_

   It clones both the pico-sdk and pico-ice-sdk, replacing Raspberry Pi's ``pico_sdk_import.cmake``.

.. _download: https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice-sdk/main/cmake/pico_ice_sdk_import.cmake

A normal CMake compilation procedure can then be followed:

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
   #include "pico-ice/flash.h"
   
   int
   main(void)
   {
       // TODO: once the API gets ready, implement an example
   
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
      $ cmake ..
      $ sed -i '/new_delete.cpp/ d' _deps/pico-sdk-src/src/rp2_common/pico_standard_link/CMakeLists.txt
      $ cmake ..
