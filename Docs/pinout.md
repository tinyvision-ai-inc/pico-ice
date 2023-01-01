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

{: .lh-0 }
```
                              ┌────────────────────────────────┐
  Outter row     Inner row    │ .───.    ┌───┐   ┌'───'┐ .───. │  Inner row      Outter row
                              │ │   │    │RGB│   │ SW2 │ │   │ │
RP2040│iCE40   RP2040│iCE40   │ '───'    └───┘   └.───.┘ '───' │ RP2040│iCE40   RP2040│iCE40
──────┼──────  ──────┼──────  │                .─┬─.           │ ──────┼──────  ──────┼──────
      ┼IOB_22a GPIO27┼CRESET  │[ ] (_)_        │SJ1│    [_] ( )│  GPIO9│IOB_35B  GPIO8┼IOB_32A
      │FLH_IO2 ADC1  │        │ F2  RST        '─┴─'    Ss  So │       │SPI_SSN       │SPI_SO
      ┼IOB_24a      GND       │( ) ( )                  ( ) ( )│ GPIO11│IOB_33b GPIO10┼IOB_34a
      │FLH_IO3       │        ├─F3───G┐                ┌Si──Ck─┤       │SPI_SI        │SPI_SCK
     3V3            3V3       │( ) ( )│                │( ) ( )│  GPIO0│IOT_38b  GPIO4┼IOT_39a
      │              │        │  3.3  │                │27  26 │       │              │
     GND            GND       │( ) ( )│                │( ) ( )│  GPIO1│IOT_36b  GPIO5┼IOT_37a
      │              │        │   G   │                │25  23 │       │              │
      ┼IOT_41a       ┼IOT_42b │( ) ( )│ ┌───────────┐  │( ) ( )│  GPIO2│IOB_23b  GPIO6┼IOB_25b
      │              │        │ 28  31│ │           │  │21  20 │       │              │G3
      ┼IOT_43a       ┼IOT_44b │( ) ( )│ │           │  │( ) ( )│  GPIO3│IOB_29b  GPIO7┼IOB_31b
      │              │        │ 32  34│ │ iCE40UP5K │  │19  18 │       │              │
      ┼IOT_48b       ┼IOT_50b │(_) ( )│ │           │  │( ) ( )│      GND            GND
      │              │        │ 36  38│ │o          │  │   G   │       │              │
      ┼IOT_51a       ┼IOT_49a │( ) ( )│ └───────────┘  │( ) ( )│      3V3            3V3
      │              │        ├─42──43┘                └──3.3──┤       │              │
GPIO14┼IOT_45a GPIO24┼IOT_46b │(_) ( ) .─┬─.            ( ) ( )│ GPIO26┼CDONE   GPIO15┼RGB1
RAM_SS│G1      GPOUT2│G0      │ SS  35 │SJ5│            ~0  B  │   ADC0│         LED_B│
      ┼IOB_20a       ┼IOB_13b │( ) ( ) '─┴─'            ( ) ( )│ GPIO28┼        GPIO13┼RGB2
      │              │        │ 11   6                  ~2  R  │   ADC2│         LED_R│
      ┼IOB_18a       ┼IOB_16a │( ) ( )                  ( ) ( )│ GPIO29┼        GPIO12┼RGB0
      │PB            │        ├─10───9┐                ┌~3──G──┤   ADC3│         LED_G│
    VCCIO_2        VCCIO_2    │( ) ( )│                │( ) ( )│ GPIO16┼        GPIO20┼
      │              │        │ Vio   │  ┌──────────┐  │A1  B1 │       │              │
     GND            GND       │( ) ( )│  │          │  │( ) ( )│ GPIO17┼        GPIO21┼
      │              │        │  G   G│  │          │  │A2  B2 │       │        GPOUT0│
      ┼IOB_3b        ┼IOB_5b  │( ) ( )│  │  RP2040  │  │( ) ( )│ GPIO18┼        GPIO22┼
      │G6            │        │ 44  45│  │          │  │A3  B3 │       │              │
      ┼IOB_0a        ┼IOB_2a  │( ) ( )│  │          │  │( ) ( )│ GPIO19┼        GPIO23┼
      │              │        │ 46  47│  └──────────┘  │A4  B4 │       │              │
      ┼IOB_4a        ┼IOB_6a  │( ) ( )│                │( ) ( )│      GND            GND
      │              │        │ 48   2│                │   G   │       │              │
      ┼IOB_9b        ┼IOB_8a  │( ) ( )│ ┌────┐         │( ) ( )│      3V3            3V3
      │              │        ├──3───4┘'│/''\│'SW1     └──3.3──┤       │              │
 SWDIO┼         RESET┼        │( ) ( ) .│\__/│.         ( ) ( )│      3V3            VCC
      │              │        │ SD      └────┘          3.3 DC │       │              │
 SWCLK┼             GND       │( ) ( )                  ( ) ( )│   3V3_STDBY        PWR_EN
      │              │        │ SC   G   ││||||||||││   Sby En │       │              │
GPIO25┼    N_USB_BOOT┼        │( ) (_)  O            O  ( ) ( )│      VBUS           GND
GPOUT3│              │        │ CK  BT  │            │  Vb  G  │       │              │
                              │  ───    │            │   .───. │
                              │ │   │   o            o   │   │ │
                              │ '───'   │            │   '───' │
                              └─────────┴────────────┴─────────┘
```

## RP2040 pinout

{: .lh-0 }
```
GPIO0 TX  IOT_38b RX  (UART)    │ Pico-FPGA bus
GPIO1 RX  IOT_36b TX  (UART)    │
GPIO2     IOB_23b               │
GPIO3     IOB_29b               │
GPIO4     IOT_39a               │
GPIO5     IOT_37b               │
GPIO6     IOB_25b_G3            │
GPIO7     IOB_31b               │

GPIO8     IOT_32a SPI_SO        │ FPGA Programming Interface
GPIO9     IOT_35b SPI_SSN       │
GPIO10    IOB_34a SPI_SCK       │
GPIO11    IOB_33b SPI_SI        │

GPIO12    LED_G                 │ LED / I²C
GPIO13    LED_R                 │

GPIO14    SRAM_SSN              │ FPGA SRAM CS

GPIO15    LED_B                 │ LED

GPIO16    PICO_PMOD_A1          │ PICO_PMOD
GPIO17    PICO_PMOD_A2          │
GPIO18    PICO_PMOD_A3          │
GPIO19    PICO_PMOD_A4          │
GPIO20    PICO_PMOD_B1          │
GPIO21    PICO_PMOD_B2          │
GPIO22    PICO_PMOD_B3          │
GPIO23    PICO_PMOD_B4          │

GPIO24    ICE_CLK               │ FPGA Clock

GPIO25    PICO_CLKOUT           │ Clock to Header

GPIO26    ADC0 CDONE            │ ADC / FPGA System
GPIO27    ADC1 CRESET           │
GPIO28    ADC2 PB               │
GPIO29    ADC3                  │

QSPI_SS    QSPI_SS              │ PICO flash
QSPI_SCLK  QSPI_SCLK            │
QSPI_SD0   QSPI_SD0             │
QSPI_SD1   QSPI_SD1             │
QSPI_SD2   QSPI_SD2             │
QSPI_SD3   QSPI_SD3             │

USB_DP     USB_P                │ USB
USB_DM     USB_N                │
```


## iCE40 pinout

{: .lh-0 }
```
IOB_0a     ICE_46               │ iCE PMOD
IOB_2a     ICE_47               │
IOB_3b_G6  ICE_44               │
IOB_4a     ICE_48               │
IOB_5b     ICE_45               │
IOB_6a     ICE_2                │
IOB_8a     ICE_4                │
IOB_9b     ICE_3                │

IOB_13b    ICE_6                │ iCE Misc
IOB_16a    ICE_9                │
IOB_18a    ICE_10 PB            │
IOB_20a    ICE_11               │

IOB_22a    ICE_FLASH_IO2        │ iCE Flash

IOB_23b    ICE_21 GPIO2         │ iCE-Pico PMOD

IOB_24a    ICE_FLASH_IO3        │ iCE Flash

IOB_25b_G3 ICE_20 GPIO6         │ iCE-Pico PMOD
IOB_29b    ICE_19 GPIO3         │
IOB_31b    ICE_18 GPIO7         │

IOB_32a    ICE_SO               │ FPGA Programming Interface
IOB_33b    ICE_SI               │
IOB_34a    ICE_SCK              │
IOB_35b    ICE_SSN              │

IOT_36b    ICE_25 GPIO1         │ iCE-Pico PMOD
IOT_37a    ICE_23 GPIO5         │
IOT_38b    ICE_27 GPIO0         │
IOT_39a    ICE_26 GPIO4         │

IOT_41a    ICE_28               │ iCE PMOD
IOT_42b    ICE_31               │
IOT_43a    ICE_32               │
IOT_44b    ICE_34               │

IOT_45a_G1 SRAM_SSN             │ FPGA SRAM CS

IOT_46a_G0 ICE_35_G0            │ iCE Misc

IOT_48b    ICE_36               │ iCE PMOD
IOT_49a    ICE_43               │
IOT_50b    ICE_38               │
IOT_51a    ICE_42               │

RGB2       LED_R                │ iCE LEDs
RGB0       LED_G                │
RGB1       LED_B                │
```

## SRAM and flash pinout

{: .lh-0 }
```
IOB_34a    ICE_SCK              │ iCE Flash
IOB_35b    ICE_SSN              │
IOB_32a    ICE_SO               │
IOB_33b    ICE_SI               │
IOB_22a    ICE_FLASH_IO2        │
IOB_24a    ICE_FLASH_IO3        │

IOB_34a    ICE_SCK              │ iCE SRAM
IOT_45a_G1 SRAM_SSN             │
IOB_32a    ICE_SO               │
IOB_33b    ICE_SI               │
IOB_22a    ICE_FLASH_IO2        │
IOB_24a    ICE_FLASH_IO3        │

QSPI_SS                         │ Pico Flash
QSPI_SCLK                       │
QSPI_SD0                        │
QSPI_SD1                        │
QSPI_SD2                        │
QSPI_SD3                        │
```
