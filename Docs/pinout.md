---
title: Pinout
layout: default
parent: pico-ice
---

# Pinout

![pinout diagram](/pinout/pinout.svg)

fullscreen: [svg](/pinout/pinout.svg) [png](/pinout/pinout.png)


## With RTL on the iCE40

The wafer names `IOB_6a`, `IOT_8b`... as well as the pin number `ICE_2`, `ICE_3`, `ICE_4`...
can be used from the RTL by picking them from this [PCF file](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/rtl/pico_ice.pcf).

For Amaranth, until this gets upstreamed, the various board resources including its pins are defined on
[`pico_ice.py`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/amaranth/pico_ice.py).



## With code on the RP2040

The FPGA pins and other signals are defined in [`pico_ice.h`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/include/boards/pico_ice.h).

The PMOD pins can also be accessed from
[`pmod.h`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/include/pmod.h) and
[`ice_pmod.h`](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/include/ice_pmod.h).
