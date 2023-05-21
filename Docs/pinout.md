---
title: Pinout
layout: default
parent: pico-ice
---

# Pinout

This diagram represents the board, with its buttons, jumpers and LEDs.
On each side are four rows of double PMODs, along with extra signals.

Their pinout is listed on each side on four vertical lines,
each representing one serie of pins of the board,
with their RP2040 and iCE40 mapping.


## Complete pinout

The wafer names `IOB_6a`, `IOT_8b`... as well as the pin number `ICE_2`, `ICE_3`, `ICE_4`...
can be used from the RTL by using the provided [PCF](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/rtl/pico_ice.pcf) file.

![pinout diagram](/pinout/diagram.svg)

{: .lh-0 }
```
┌───┬───┬────┬────┬────┬────┐ 
│3V3│GND│  4 │  3 │  2 │  1 │ 
├───┼───┼────┼────┼────┼────┤ 
│3V3│GND│ 10 │  9 │  8 │  7 │ 
└───┴───┼────┼────┼────┼────┤ 
   GPIO │IO4 │IO3 │IO2 │IO1 │ 
    I2C │SDA │SCL │RST │INT │ 
    I2S │BCLK│ADC │DAC │LRCLK 
    SPI │SCK │MISO│MOSI│CS  │ 
   UART │RTS │RXD │TXD │CTS │ 
HBridge │SB  │SA  │EN  │DIR │ 
```
