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

{: .lh-0 }
```
                              ┌────────────────────────────────┐
  Outter row     Inner row    │ .───.    ┌───┐   ┌┴───┴┐ .───. │  Inner row      Outter row
                              │ │   │    │RGB│   │ SW2 │ │   │ │
RP2040│iCE40   RP2040│iCE40   │ '───'    └───┘   └┬───┬┘ '───' │ RP2040│iCE40   RP2040│iCE40
──────┼──────  ──────┼──────  │                ┌─┬─┐           │ ──────┼──────  ──────┼──────
      █IOB_22a GPIO27█CRESET  │[█] (█)         │SJ1│    [█] (█)│  GPIO9█IOB_35B  GPIO8█IOB_32A
      │FLH_IO2 ADC1  │        │ F2  RST        └─┴─┘    Ss  So │       │SPI_SSN       │SPI_SO
      █IOB_24a    GND█GND     │(█) (█)                  (█) (█)│ GPIO11█IOB_33b GPIO10█IOB_34a
      │FLH_IO3       │        ├─F3───G┐                ┌Si──Ck─┤       │SPI_SI        │SPI_SCK
   3V3█3V3        3V3█3V3     │(█) (█)│                │(█) (█)│  GPIO0█IOT_38b  GPIO4█IOT_39a
      │              │        │  3.3  │                │27  26 │       │              │
   GND█GND        GND█GND     │(█) (█)│                │(█) (█)│  GPIO1█IOT_36b  GPIO5█IOT_37a
      │              │        │   G   │                │25  23 │       │              │
      █IOT_41a       █IOT_42b │(█) (█)│ ┌───────────┐  │(█) (█)│  GPIO2█IOB_23b  GPIO6█IOB_25b
      │              │        │ 28  31│ │           │  │21  20 │       │              │G3
      █IOT_43a       █IOT_44b │(█) (█)│ │           │  │(█) (█)│  GPIO3█IOB_29b  GPIO7█IOB_31b
      │              │        │ 32  34│ │ iCE40UP5K │  │19  18 │       │              │
      █IOT_48b       █IOT_50b │(█) (█)│ │           │  │(█) (█)│    GND█GND        GND█GND
      │              │        │ 36  38│ │           │  │   G   │       │              │
      █IOT_51a       █IOT_49a │(█) (█)│ └───────────┘  │(█) (█)│    3V3█3V3        3V3█3V3
      │              │        ├─42──43┘                └──3.3──┤       │              │
GPIO14█IOT_45a GPIO24█IOT_46b │(█) (█) ┌─┬─┐            (█) (█)│ GPIO26█CDONE   GPIO15█RGB1
RAM_SS│G1      GPOUT2│G0      │ SS  35 │SJ5│            ~0  B  │   ADC0│         LED_B│
      █IOB_20a       █IOB_13b │(█) (█) └─┴─┘            (█) (█)│ GPIO28█        GPIO13█RGB2
      │              │        │ 11   6                  ~2  R  │   ADC2│         LED_R│
      █IOB_18a       █IOB_16a │(█) (█)                  (█) (█)│ GPIO29█        GPIO12█RGB0
      │PB            │        ├─10───9┐                ┌~3──G──┤   ADC3│         LED_G│
VCCIO2█VCCIO2  VCCIO2█VCCIO2  │(█) (█)│                │(█) (█)│ GPIO16█        GPIO20█
      │              │        │ Vio   │  ┌──────────┐  │A1  B1 │       │              │
   GND█GND        GND█GND     │(█) (█)│  │          │  │(█) (█)│ GPIO17█        GPIO21█
      │              │        │  G   G│  │          │  │A2  B2 │       │        GPOUT0│
      █IOB_3b        █IOB_5b  │(█) (█)│  │  RP2040  │  │(█) (█)│ GPIO18█        GPIO22█
      │G6            │        │ 44  45│  │          │  │A3  B3 │       │              │
      █IOB_0a        █IOB_2a  │(█) (█)│  │          │  │(█) (█)│ GPIO19█        GPIO23█
      │              │        │ 46  47│  └──────────┘  │A4  B4 │       │              │
      █IOB_4a        █IOB_6a  │(█) (█)│                │(█) (█)│    GND█GND        GND█GND
      │              │        │ 48   2│                │   G   │       │              │
      █IOB_9b        █IOB_8a  │(█) (█)│  ┌───┐         │(█) (█)│    3V3█3V3        3V3█3V3
      │              │        ├──3───4┘  ┤SW1├         └──3.3──┤       │              │
 SWDIO█         RESET█        │(█) (█)   ┤   ├          (█) (█)│    3V3█3V3        Vcc█Vcc
      │              │        │ SD       └───┘          3.3 DC │       │              │
 SWCLK█           GND█GND     │(█) (█)                  (█) (█)│3V3_SBY█3V3_SBY PWR_EN█PWR_EN
      │              │        │ SC   G   ││||||||||││   Sby En │       │              │
GPIO25█    N_USB_BOOT█        │(█) (█)  O            O  (█) (█)│   Vbus█Vbus       GND█GND
GPOUT3│              │        │ CK  BT  │            │  Vb  G  │       │              │
                              │ .───.   │            │   .───. │
                              │ │   │   o            o   │   │ │
                              │ '───'   │            │   '───' │
                              └─────────┴────────────┴─────────┘
```


## PMOD pinout

These PMOD names can be used from the RTL by using the provided
[PCF](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/rtl/pico_ice.pcf) file.

Using `A` for the top row and `B` for the bottom row:
`ICE_PMOD1A_SDA`, `ICE_PMOD2B_IO3`, `ICE_PMOD0A_MISO`...

{: .lh-0 }
```
                              ┌────────────────────────────────┐
                              │ .───.    ┌───┐   ┌┴───┴┐ .───. │
                              │ │   │    │RGB│   │ SW2 │ │   │ │
                              │ '───'    └───┘   └┬───┬┘ '───' │
                              │                ┌─┬─┐           │
                              │[█] (█)         │SJ1│    [█] (█)│
                              │ F2  RST        └─┴─┘    Ss  So │
ICE_PMOD1                     │(█) (█)                  (█) (█)│ ICE_PMOD2 (ICE_PICO_PMOD)
┌───┬───┬────┬────┬────┬────┐ ├─F3───G┐                ┌Si──Ck─┤ ┌───┬───┬────┬────┬────┬────┐
│3V3│GND│ 31 │ 34 │ 38 │ 43 │ │(█) (█)│                │(█) (█)│ │3V3│GND│ 19 │ 21 │ 25 │ 27 │
├───┼───┼────┼────┼────┼────┤ │  3.3  │                │27  26 │ ├───┼───┼────┼────┼────┼────┤
│3V3│GND│ 28 │ 32 │ 36 │ 42 │ │(█) (█)│                │(█) (█)│ │3V3│GND│ 18 │ 20 │ 23 │ 26 │
└───┴───┼────┼────┼────┼────┤ │   G   │                │25  23 │ └───┴───┼────┼────┼────┼────┤
   GPIO │IO4 │IO3 │IO2 │IO1 │ │(█) (█)│ ┌───────────┐  │(█) (█)│    GPIO │IO4 │IO3 │IO2 │IO1 │
    I2C │SDA │SCL │RST │INT │ │ 28  31│ │           │  │21  20 │     I2C │SDA │SCL │RST │INT │
    I2S │BCLK│ADC │DAC │LRCLK │(█) (█)│ │           │  │(█) (█)│     I2S │BCLK│ADC │DAC │LRCLK
    SPI │SCK │MISO│MOSI│CS  │ │ 32  34│ │ iCE40UP5K │  │19  18 │     SPI │SCK │MISO│MOSI│CS  │
   UART │RTS │RXD │TXD │CTS │ │(█) (█)│ │           │  │(█) (█)│    UART │RTS │RXD │TXD │CTS │
HBridge │SB  │SA  │EN  │DIR │ │ 36  38│ │           │  │   G   │ HBridge │SB  │SA  │EN  │DIR │
                              │(█) (█)│ └───────────┘  │(█) (█)│
                              ├─42──43┘                └──3.3──┤
                              │(█) (█) ┌─┬─┐            (█) (█)│
                              │ SS  35 │SJ5│            ~0  B  │
                              │(█) (█) └─┴─┘            (█) (█)│
                              │ 11   6                  ~2  R  │
ICE_PMOD0                     │(█) (█)                  (█) (█)│ PICO_PMOD
┌───┬───┬────┬────┬────┬────┐ ├─10───9┐                ┌~3──G──┤ ┌───┬───┬────┬────┬────┬────┐
│Vio│GND│ 45 │ 47 │  2 │  4 │ │(█) (█)│                │(█) (█)│ │3V3│GND│GP19│GP18│GP17│GP16│
├───┼───┼────┼────┼────┼────┤ │ Vio   │  ┌──────────┐  │A1  B1 │ ├───┼───┼────┼────┼────┼────┤
│Vio│GND│ 44 │ 46 │ 48 │  3 │ │(█) (█)│  │          │  │(█) (█)│ │3V3│GND│GP23│GP22│GP21│GP20│
└───┴───┼────┼────┼────┼────┤ │  G   G│  │          │  │A2  B2 │ └───┴───┼────┼────┼────┼────┤
   GPIO │IO4 │IO3 │IO2 │IO1 │ │(█) (█)│  │  RP2040  │  │(█) (█)│    GPIO │IO4 │IO3 │IO2 │IO1 │
    I2C │SDA │SCL │RST │INT │ │ 44  45│  │          │  │A3  B3 │     I2C │SDA │SCL │RST │INT │
    I2S │BCLK│ADC │DAC │LRCLK │(█) (█)│  │          │  │(█) (█)│     I2S │BCLK│ADC │DAC │LRCLK
    SPI │SCK │MISO│MOSI│CS  │ │ 46  47│  └──────────┘  │A4  B4 │     SPI │SCK │MISO│MOSI│CS  │
   UART │RTS │RXD │TXD │CTS │ │(█) (█)│                │(█) (█)│    UART │RTS │RXD │TXD │CTS │
HBridge │SB  │SA  │EN  │DIR │ │ 48   2│                │   G   │ HBridge │SB  │SA  │EN  │DIR │
                              │(█) (█)│  ┌───┐         │(█) (█)│
                              ├──3───4┘  ┤SW1├         └──3.3──┤
                              │(█) (█)   ┤   ├          (█) (█)│
                              │ SD       └───┘          3.3 DC │
                              │(█) (█)                  (█) (█)│
                              │ SC   G   ││||||||||││   Sby En │
                              │(█) (█)  O            O  (█) (█)│
                              │ CK  BT  │            │  Vb  G  │
                              │ .───.   │            │   .───. │
                              │ │   │   o            o   │   │ │
                              │ '───'   │            │   '───' │
                              └─────────┴────────────┴─────────┘
```
