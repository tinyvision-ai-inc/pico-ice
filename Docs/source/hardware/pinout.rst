======
Pinout
======

.. code-block::

                                       
                           ,────┬───────────────────────┬────.
                          /.───.│( ) ( ) ( ) ( ) ( ) ( )│.───.\
                         . │   ││      S P A R E S      ││   │ .
                         │ '───'│( ) ( ) ( ) ( ) ( ) ( )│'───' │
    ICE40           PCB  │      └─────────────────┬───┬─┘J7    │  PCB     ICE40      RP2040
    ──────          ───  │  LED3    ┌─────┐       ├SJ1┤    o   │  ───     ─────      ──────
    IOB_8a       ICE_04 ─┼───┐───┐  │ SW2 │       └───┘┌───┌───┼─ +3V3
    IOB_9b       ICE_03 ─┼( )└[ ]│  └─────┘   LED2     │( )┘[ ]┼─ +3V3
    IOB_6a       ICE_02 ─┼───┐   │                     │   ┌───┼─ GND
    IOB_4a       ICE_48 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOB_2a       ICE_47 ─┼───┐   │I                   I│   ┌───┼─ ICE_19  IOB_29b    GPIO7
    IOB_0a       ICE_46 ─┼( )└( )│C                   C│( )┘( )┼─ ICE_20  IOB_25b_G3 GPIO10
    IOB_5b       ICE_45 ─┼───┐   │E                   E│   ┌───┼─ ICE_21  IOB_23b    GPIO6
    IOB_3b_G6    ICE_44 ─┼( )└( )│| ┌───────────┐     |│( )┘( )┼─ ICE_18  IOB_31b    GPIO11
                    GND ─┼───┐   │A │           │     S│   ┌───┼─ ICE_25  IOT_36b    GPIO5
                    GND ─┼( )└( )│  │           │      │( )┘( )┼─ ICE_23  IOT_37a    GPIO9
                   +3V3 ─┼───┐   │  │ ICE40UP5K │      │   ┌───┼─ ICE_27  IOT_38b    GPIO4
                   +3V3 ─┼( )└( )│  │           │      │[ ]┘( )┼─ ICE_26  IOT_39a    GPIO8
    IOB_18a      ICE_10 ─┼───┐───┤  │.          │      ├───┌───┼─ GND
    IOT_46a_G0   ICE_35 ─┼( )└[ ]│I └───────────┘      │( )┘( )┼─ NRESET             RUN
    IOB_20a      ICE_11 ─┼───┐   │C            o       │   ┌───┼─ VBUS
   (GPIO25) PICO_CLKOUT ─┼( )└( )│E┌─┬─┐┌─┬─┐ TP1      │( )┘( )┼─ ADC2               GPIO28
    IOB_13b      ICE_06 ─┼───┐   │|│SJ5││SJ6│          │   ┌───┼─ ICE_DONE_ADC0      GPIO26
    IOB_16a      ICE_09 ─┼( )└( )│H└─┴─┘└─┴─┘          │[ ]┘( )┼─ ADC3               GPIO29
    IOT_49a      ICE_43 ─┼───┐───│                     ├───┌───┼─ +3V3
    IOT_51a      ICE_42 ─┼( )└[ ]│                     │( )┘( )┼─ +3V3
    IOT_50b      ICE_38 ─┼───┐   │                     │   ┌───┼─ GND
    IOT_48b      ICE_36 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOT_44b      ICE_34 ─┼───┐   │I   ┌───────────┐   P│   ┌───┼─ PICO_PMOD_A4       GPIO15
    IOT_43a      ICE_32 ─┼( )└( )│C   │           │   I│( )┘( )┼─ PICO_PMOD_B4       GPIO19
    IOT_42b      ICE_31 ─┼───┐   │E   │           │   C│   ┌───┼─ PICO_PMOD_A3       GPIO14
    IOT_41a      ICE_28 ─┼( )└( )│|   │  RP2040   │   O│( )┘( )┼─ PICO_PMOD_B3       GPIO18
                    GND ─┼───┐   │B   │           │    │   ┌───┼─ PICO_PMOD_A2       GPIO13
                    GND ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B2       GPIO17
                   +3V3 ─┼───┐   │    └───────────┘    │   ┌───┼─ PICO_PMOD_A1       GPIO12
                   +3V3 ─┼( )└( )│                     │[ ]┘( )┼─ PICO_PMOD_B1       GPIO16
                    SWD ─┼───┐───│                     ├───┌───┼─ USB_BOOT
                  SWCLK ─┼[ ]└( )│ ┌────┐        LED4  │[ ]┘( )┼─ GND
                         ├───────┘ │SW1 │              └───────┤
                         │SWC SWD  │    │              BOOT GND│
                         │         └────┘                      │
                         │            ││ ||||||| ││            │
                         │          O               O          │
                         │          │               │          │
                         │  ───     │      USB      │    .───. │
                         . │   │    o               o    │   │ .
                          \'───'    │               │    '───'/
                           `─────────────────────────────────'


RP2040 pinout
-------------

.. code-block::

   GPIO0     ICE_SO                │ FPGA programming interface
   GPIO1     ICE_SSN               │
   GPIO2     ICE_SCK               │
   GPIO3     ICE_SI                │

   GPIO4     IOT_38b               │ Pico-FPGA bus
   GPIO5     IOT_36b               │
   GPIO6     IOB_23b               │
   GPIO7     IOB_29b               │
   GPIO8     IOT_39a               │
   GPIO9     IOT_37a               │
   GPIO10    IOB_25b_G3            │
   GPIO11    IOB_31b               │

   GPIO12    PICO_PMOD_A1          │ Pico PMOD
   GPIO13    PICO_PMOD_A2          │
   GPIO14    PICO_PMOD_A3          │
   GPIO15    PICO_PMOD_A4          │
   GPIO16    PICO_PMOD_B1          │
   GPIO17    PICO_PMOD_B2          │
   GPIO18    PICO_PMOD_B3          │
   GPIO19    PICO_PMOD_B4          │

   GPIO20    SRAM_SSN              │ CS of the FPGA SRAM chip

   GPIO21    IOT_46b_G0            │ ICE_CLK (FPGA Clock)

   GPIO22    PICO_LED_R            │ LED
   GPIO23    PICO_LED_G            │
   GPIO24    PICO_LED_B            │

   GPIO25    PICO_CLKOUT           │ clock PMOD

   GPIO26    ADC0/CDONE            │ ADC PMOD / ICE_DONE (FPGA status pin)

   GPIO27    ADC1/CRESET           │ ADC PMOD / ICE_RSTn (FPGA nreset pin)

   GPIO28    ADC2                  │ extra ADCs pins
   GPIO29    ADC3                  │

   QSPI_SS    QSPI_SS              │ PICO flash
   QSPI_SCLK  QSPI_SCLK            │
   QSPI_SD0   QSPI_SD0             │
   QSPI_SD1   QSPI_SD1             │
   QSPI_SD2   QSPI_SD2             │
   QSPI_SD3   QSPI_SD3             │


iCE40 pinout
------------

.. code-block::

   IOB_0a     ICE_PMOD_A_B3        │ ICE PMOD A
   IOB_2a     ICE_PMOD_A_A3        │
   IOB_3b_G6  ICE_PMOD_A_B4        │
   IOB_4a     ICE_PMOD_A_B2        │
   IOB_5b     ICE_PMOD_A_A4        │
   IOB_6a     ICE_PMOD_A_A2        │
   IOB_8a     ICE_PMOD_A_A1        │
   IOB_9b     ICE_PMOD_A_B1        │

   IOB_13b    ICE_PMOD_H_5         │ ICE PMOD H
   IOB_16a    ICE_PMOD_H_6         │
   IOB_18a    ICE_PMOD_H_1         │
   IOB_20a    ICE_PMOD_H_3         │

   IOB_22a    ICE_FLASH_IO2        │ FPGA flash and SRAM

   IOB_23b    ICE_PMOD_S_A3/GPIO6  │ ICE PMOD S

   IOB_24a    ICE_FLASH_IO3        │ FPGA flash and SRAM

   IOB_25b_G3 ICE_PMOD_S_B4/GPIO10 │ ICE PMOD S
   IOB_29b    ICE_PMOD_S_A4/GPIO7  │
   IOB_31b    ICE_PMOD_S_B3/GPIO11 │

   IOB_32a    ICE_SO               │ FPGA flash and SRAM
   IOB_33b    ICE_SI               │
   IOB_34a    ICE_SCK              │
   IOB_35b    ICE_SSN              │

   IOT_36b    ICE_PMOD_S_A2/GPIO5  │ ICE PMOD S
   IOT_37a    ICE_PMOD_S_B2/GPIO9  │
   IOT_38b    ICE_PMOD_S_A1/GPIO4  │
   IOT_39a    ICE_PMOD_S_B1/GPIO8  │

   IOT_41a    ICE_PMOD_B_B4        │ ICE PMOD B
   IOT_42b    ICE_PMOD_B_A4        │
   IOT_43a    ICE_PMOD_B_B3        │
   IOT_44b    ICE_PMOD_B_A3        │

   IOT_45a_G1 SRAM_SSN             │ FPGA flash and SRAM

   IOT_46a_G0 ICE_PMOD_H_2         │ ICE PMOD H

   IOT_48b    ICE_PMOD_B_B2        │ ICE PMOD B
   IOT_49a    ICE_PMOD_B_A1        │
   IOT_50b    ICE_PMOD_B_A2        │
   IOT_51a    ICE_PMOD_B_B1        │


SRAM and flash pinout
---------------------

.. code-block::

   IOB_34a    ICE_SCK              │ FPGA flash
   IOB_35b    ICE_SSN              │
   IOB_32a    ICE_SO               │
   IOB_33b    ICE_SI               │
   IOB_22a    ICE_FLASH_IO2        │
   IOB_24a    ICE_FLASH_IO3        │

   IOB_34a    ICE_SCK              │ FPGA SRAM
   IOT_45a_G1 SRAM_SSN             │
   IOB_32a    ICE_SO               │
   IOB_33b    ICE_SI               │
   IOB_22a    ICE_FLASH_IO2        │
   IOB_24a    ICE_FLASH_IO3        │

   QSPI_SS    QSPI_SS              │ PICO flash
   QSPI_SCLK  QSPI_SCLK            │
   QSPI_SD0   QSPI_SD0             │
   QSPI_SD1   QSPI_SD1             │
   QSPI_SD2   QSPI_SD2             │
   QSPI_SD3   QSPI_SD3             │
