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

The wafer names `IOB_6a`, `IOT_8b`... as well as the pin number `ICE_2`, `ICE_3`, `ICE_4`... can be used in RTL projects, as they are defined in your file (see below).

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

These PMOD names can be used from the RTL by using your pcf file on Yosys (see below).

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


## Yosys/NextPNR pinou file

NextPNR only implements a name per pin, no aliases.

Below is a reference chart with name of Signals and PMODs matching the references above.
You can build your own `pico_ice.pcf` from it,
keeping in mind that numbers on the right can appear only once for each.


### Signals as in KiCAD

They are takein after the package pin number.

```
set_io -nowarn ICE_2            2
set_io -nowarn ICE_3            3
set_io -nowarn ICE_4            4
set_io -nowarn ICE_6            6
set_io -nowarn ICE_9            9
set_io -nowarn ICE_10           10
set_io -nowarn ICE_11           11
set_io -nowarn ICE_18           18
set_io -nowarn ICE_19           19
set_io -nowarn ICE_20_G3        20
set_io -nowarn ICE_21           21
set_io -nowarn ICE_23           23
set_io -nowarn ICE_25           25
set_io -nowarn ICE_26           26
set_io -nowarn ICE_27           27
set_io -nowarn ICE_28           28
set_io -nowarn ICE_31           31
set_io -nowarn ICE_32           32
set_io -nowarn ICE_34           34
set_io -nowarn ICE_35_G0        35
set_io -nowarn ICE_36           36
set_io -nowarn ICE_38           38
set_io -nowarn ICE_42           42
set_io -nowarn ICE_43           43
set_io -nowarn ICE_44_G6        44
set_io -nowarn ICE_45           45
set_io -nowarn ICE_46           46
set_io -nowarn ICE_47           47
set_io -nowarn ICE_48           48
set_io -nowarn ICE_FLASH_IO2    12
set_io -nowarn ICE_FLASH_IO3    13
set_io -nowarn ICE_PB           10
set_io -nowarn ICE_SO           14
set_io -nowarn ICE_SI           17
set_io -nowarn ICE_SCK          15
set_io -nowarn ICE_SSN          16
set_io -nowarn SRAM_SS          37
set_io -nowarn LED_G            39
set_io -nowarn LED_B            40
set_io -nowarn LED_R            41
```


### Signals as in the silicon die

They are the internal numbers:

- IOB means IO at the bottom of the die.
- IOT means IO at the top of the die.

```
set_io -nowarn IOB_6a           2
set_io -nowarn IOB_9b           3
set_io -nowarn IOB_8a           4
set_io -nowarn IOB_13b          6
set_io -nowarn IOB_16a          9
set_io -nowarn IOB_18a          10
set_io -nowarn IOB_20a          11
set_io -nowarn IOB_31b          18
set_io -nowarn IOB_29b          19
set_io -nowarn IOB_25b          20
set_io -nowarn IOT_23b          21
set_io -nowarn IOT_37a          23
set_io -nowarn IOT_36b          25
set_io -nowarn IOT_39a          26
set_io -nowarn IOT_38b          27
set_io -nowarn IOT_41a          28
set_io -nowarn IOT_42b          31
set_io -nowarn IOT_43a          32
set_io -nowarn IOT_44b          34
set_io -nowarn IOT_46b          35
set_io -nowarn IOT_48b          36
set_io -nowarn IOT_50b          38
set_io -nowarn IOT_51a          42
set_io -nowarn IOT_49a          43
set_io -nowarn IOB_3b           44
set_io -nowarn IOB_5b           45
set_io -nowarn IOB_0a           46
set_io -nowarn IOB_2b           47
set_io -nowarn IOB_4a           48
set_io -nowarn IOB_22a          12
set_io -nowarn IOB_24a          13
set_io -nowarn IOB_18a          10
set_io -nowarn IOB_32a          14
set_io -nowarn IOB_33b          17
set_io -nowarn IOB_34a          15
set_io -nowarn IOB_35b          16
set_io -nowarn IOT_45a          37
set_io -nowarn RGB0             39
set_io -nowarn RGB1             40
set_io -nowarn RGB2             41
```


### PMOD names

<https://digilent.com/reference/pmod/start>

You will have to keep only one set of signal for each block, for instance, GPIO, or I2C, or SPI, or I2S...

```
# ICE_PMOD0A (near USB) top row
# GPIO
set_io -nowarn ICE_PMOD0A_IO4   45
set_io -nowarn ICE_PMOD0A_IO3   47
set_io -nowarn ICE_PMOD0A_IO2   2
set_io -nowarn ICE_PMOD0A_IO1   4
# I2C
set_io -nowarn ICE_PMOD0A_SDA   45
set_io -nowarn ICE_PMOD0A_SCL   47
set_io -nowarn ICE_PMOD0A_RST   2
set_io -nowarn ICE_PMOD0A_INT   4
# I2S
set_io -nowarn ICE_PMOD0A_BCLK  45
set_io -nowarn ICE_PMOD0A_ADC   47
set_io -nowarn ICE_PMOD0A_DAC   2
set_io -nowarn ICE_PMOD0A_LRCLK 4
# SPI
set_io -nowarn ICE_PMOD0A_SCK   45
set_io -nowarn ICE_PMOD0A_MISO  47
set_io -nowarn ICE_PMOD0A_MOSI  2
set_io -nowarn ICE_PMOD0A_CS    4
# UART
set_io -nowarn ICE_PMOD0A_RTS   45
set_io -nowarn ICE_PMOD0A_RXD   47
set_io -nowarn ICE_PMOD0A_TXD   2
set_io -nowarn ICE_PMOD0A_CTS   4
# HBridge
set_io -nowarn ICE_PMOD0A_SB    45
set_io -nowarn ICE_PMOD0A_SA    47
set_io -nowarn ICE_PMOD0A_EN    2
set_io -nowarn ICE_PMOD0A_DIR   4

# ICE_PMOD0B (near USB) bottom row
# GPIO
set_io -nowarn ICE_PMOD0B_IO4   44
set_io -nowarn ICE_PMOD0B_IO3   46
set_io -nowarn ICE_PMOD0B_IO2   48
set_io -nowarn ICE_PMOD0B_IO1   3
# I2C
set_io -nowarn ICE_PMOD0B_SDA   44
set_io -nowarn ICE_PMOD0B_SCL   46
set_io -nowarn ICE_PMOD0B_RST   48
set_io -nowarn ICE_PMOD0B_INT   3
# I2S
set_io -nowarn ICE_PMOD0B_BCLK  44
set_io -nowarn ICE_PMOD0B_ADC   46
set_io -nowarn ICE_PMOD0B_DAC   48
set_io -nowarn ICE_PMOD0B_LRCLK 3
# SPI
set_io -nowarn ICE_PMOD0B_SCK   44
set_io -nowarn ICE_PMOD0B_MISO  46
set_io -nowarn ICE_PMOD0B_MOSI  48
set_io -nowarn ICE_PMOD0B_CS    3
# UART
set_io -nowarn ICE_PMOD0B_RTS   44
set_io -nowarn ICE_PMOD0B_RXD   46
set_io -nowarn ICE_PMOD0B_TXD   48
set_io -nowarn ICE_PMOD0B_CTS   3
# HBridge
set_io -nowarn ICE_PMOD0B_SB    44
set_io -nowarn ICE_PMOD0B_SA    46
set_io -nowarn ICE_PMOD0B_EN    48
set_io -nowarn ICE_PMOD0B_DIR   3

# ICE_PMOD1A (near LED) top row
# GPIO
set_io -nowarn ICE_PMOD1A_IO4   31
set_io -nowarn ICE_PMOD1A_IO3   34
set_io -nowarn ICE_PMOD1A_IO2   38
set_io -nowarn ICE_PMOD1A_IO1   43
# I2C
set_io -nowarn ICE_PMOD1A_SDA   31
set_io -nowarn ICE_PMOD1A_SCL   34
set_io -nowarn ICE_PMOD1A_RST   38
set_io -nowarn ICE_PMOD1A_INT   43
# I2S
set_io -nowarn ICE_PMOD1A_BCLK  31
set_io -nowarn ICE_PMOD1A_ADC   34
set_io -nowarn ICE_PMOD1A_DAC   38
set_io -nowarn ICE_PMOD1A_LRCLK 43
# SPI
set_io -nowarn ICE_PMOD1A_SCK   31
set_io -nowarn ICE_PMOD1A_MISO  34
set_io -nowarn ICE_PMOD1A_MOSI  38
set_io -nowarn ICE_PMOD1A_CS    43
# UART
set_io -nowarn ICE_PMOD1A_RTS   31
set_io -nowarn ICE_PMOD1A_RXD   34
set_io -nowarn ICE_PMOD1A_TXD   38
set_io -nowarn ICE_PMOD1A_CTS   43
# HBridge
set_io -nowarn ICE_PMOD1A_SB    31
set_io -nowarn ICE_PMOD1A_SA    34
set_io -nowarn ICE_PMOD1A_EN    38
set_io -nowarn ICE_PMOD1A_DIR   43

# ICE_PMOD1B (near LED) bottom row
# GPIO
set_io -nowarn ICE_PMOD1B_IO4   28
set_io -nowarn ICE_PMOD1B_IO3   32
set_io -nowarn ICE_PMOD1B_IO2   36
set_io -nowarn ICE_PMOD1B_IO1   42
# I2C
set_io -nowarn ICE_PMOD1B_SDA   28
set_io -nowarn ICE_PMOD1B_SCL   32
set_io -nowarn ICE_PMOD1B_RST   36
set_io -nowarn ICE_PMOD1B_INT   42
# I2S
set_io -nowarn ICE_PMOD1B_BCLK  28
set_io -nowarn ICE_PMOD1B_ADC   32
set_io -nowarn ICE_PMOD1B_DAC   36
set_io -nowarn ICE_PMOD1B_LRCLK 42
# SPI
set_io -nowarn ICE_PMOD1B_SCK   28
set_io -nowarn ICE_PMOD1B_MISO  32
set_io -nowarn ICE_PMOD1B_MOSI  36
set_io -nowarn ICE_PMOD1B_CS    42
# UART
set_io -nowarn ICE_PMOD1B_RTS   28
set_io -nowarn ICE_PMOD1B_RXD   32
set_io -nowarn ICE_PMOD1B_TXD   36
set_io -nowarn ICE_PMOD1B_CTS   42
# HBridge
set_io -nowarn ICE_PMOD1B_SB    28
set_io -nowarn ICE_PMOD1B_SA    32
set_io -nowarn ICE_PMOD1B_EN    36
set_io -nowarn ICE_PMOD1B_DIR   42

# ICE_PMOD2A (near LED, shared with RP2040) top row
# GPIO
set_io -nowarn ICE_PMOD2A_IO4   19
set_io -nowarn ICE_PMOD2A_IO3   21
set_io -nowarn ICE_PMOD2A_IO2   25
set_io -nowarn ICE_PMOD2A_IO1   27
# I2C
set_io -nowarn ICE_PMOD2A_SDA   19
set_io -nowarn ICE_PMOD2A_SCL   21
set_io -nowarn ICE_PMOD2A_RST   25
set_io -nowarn ICE_PMOD2A_INT   27
# I2S
set_io -nowarn ICE_PMOD2A_BCLK  19
set_io -nowarn ICE_PMOD2A_ADC   21
set_io -nowarn ICE_PMOD2A_DAC   25
set_io -nowarn ICE_PMOD2A_LRCLK 27
# SPI
set_io -nowarn ICE_PMOD2A_SCK   19
set_io -nowarn ICE_PMOD2A_MISO  21
set_io -nowarn ICE_PMOD2A_MOSI  25
set_io -nowarn ICE_PMOD2A_CS    27
# UART
set_io -nowarn ICE_PMOD2A_RTS   19
set_io -nowarn ICE_PMOD2A_RXD   21
set_io -nowarn ICE_PMOD2A_TXD   25
set_io -nowarn ICE_PMOD2A_CTS   27
# HBridge
set_io -nowarn ICE_PMOD2A_SB    19
set_io -nowarn ICE_PMOD2A_SA    21
set_io -nowarn ICE_PMOD2A_EN    25
set_io -nowarn ICE_PMOD2A_DIR   27

# ICE_PMOD2B (near LED, shared with RP2040) bottom row
# GPIO
set_io -nowarn ICE_PMOD2B_IO4   18
set_io -nowarn ICE_PMOD2B_IO3   20
set_io -nowarn ICE_PMOD2B_IO2   23
set_io -nowarn ICE_PMOD2B_IO1   26
# I2C
set_io -nowarn ICE_PMOD2B_SDA   18
set_io -nowarn ICE_PMOD2B_SCL   20
set_io -nowarn ICE_PMOD2B_RST   23
set_io -nowarn ICE_PMOD2B_INT   26
# I2S
set_io -nowarn ICE_PMOD2B_BCLK  18
set_io -nowarn ICE_PMOD2B_ADC   20
set_io -nowarn ICE_PMOD2B_DAC   23
set_io -nowarn ICE_PMOD2B_LRCLK 26
# SPI
set_io -nowarn ICE_PMOD2B_SCK   18
set_io -nowarn ICE_PMOD2B_MISO  20
set_io -nowarn ICE_PMOD2B_MOSI  23
set_io -nowarn ICE_PMOD2B_CS    26
# UART
set_io -nowarn ICE_PMOD2B_RTS   18
set_io -nowarn ICE_PMOD2B_RXD   20
set_io -nowarn ICE_PMOD2B_TXD   23
set_io -nowarn ICE_PMOD2B_CTS   26
# HBridge
set_io -nowarn ICE_PMOD2B_SB    18
set_io -nowarn ICE_PMOD2B_SA    20
set_io -nowarn ICE_PMOD2B_EN    23
set_io -nowarn ICE_PMOD2B_DIR   26
```
