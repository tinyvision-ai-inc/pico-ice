======
Pinout
======

.. code-block::

                           ,────┬───────────────────────┬────.
                          /.───.│( ) ( ) ( ) ( ) ( ) ( )│.───.\
                         . │   ││                       ││   │ .
                         │ '───'│( ) ( ) ( ) ( ) ( ) ( )│'───' │
    ICE40           PCB  │      └─────────────────┬───┬─┘J7    │  PCB     ICE40      RP2040
    ──────          ───  │  LED3    ┌─────┐       ├SJ1┤    o   │  ───     ─────      ──────
    IOB_8a       ICE_04 ─┼───┐───┐  │ SW2 │       └───┘┌───┌───┼─ +3V3
    IOB_9b       ICE_03 ─┼( )└[ ]│  └─────┘   LED2     │( )┘[ ]┼─ +3V3
    IOB_6a       ICE_02 ─┼───┐   │                     │   ┌───┼─ GND
    IOB_4a       ICE_48 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOB_2a       ICE_47 ─┼───┐   │                     │   ┌───┼─ ICE_19  IOB_29b    GPIO7
    IOB_0a       ICE_46 ─┼( )└( )│                     │( )┘( )┼─ ICE_20  IOB_25b_G3 GPIO10
    IOB_5b       ICE_45 ─┼───┐   │                     │   ┌───┼─ ICE_21  IOB_23b    GPIO6
    IOB_3b_G6    ICE_44 ─┼( )└( )│  ┌───────────┐      │( )┘( )┼─ ICE_18  IOB_31b    GPIO11
                    GND ─┼───┐   │  │           │      │   ┌───┼─ ICE_25  IOT_36b    GPIO5
                    GND ─┼( )└( )│  │           │      │( )┘( )┼─ ICE_23  IOT_37a    GPIO9
                   +3V3 ─┼───┐   │  │ ICE40UP5K │      │   ┌───┼─ ICE_27  IOT_38b    GPIO4
                   +3V3 ─┼( )└( )│  │           │      │[ ]┘( )┼─ ICE_26  IOT_39a    GPIO8
    IOB_18a      ICE_10 ─┼───┐───┤  │.          │      ├───┌───┼─ GND
    IOT_46a_G0   ICE_35 ─┼( )└[ ]│  └───────────┘      │( )┘( )┼─ NRESET             RUN
    IOB_20a      ICE_11 ─┼───┐   │             o       │   ┌───┼─ VBUS
   (GPIO25) PICO_CLKOUT ─┼( )└( )│┌─┬─┐┌─┬─┐  TP1      │( )┘( )┼─ ADC2               GPIO28
    IOB_13b      ICE_06 ─┼───┐   ││SJ5││SJ6│           │   ┌───┼─ ICE_DONE_ADC0      GPIO26
    IOB_16a      ICE_09 ─┼( )└( )│└─┴─┘└─┴─┘           │[ ]┘( )┼─ ADC3               GPIO29
    IOT_49a      ICE_43 ─┼───┐───│                     ├───┌───┼─ +3V3
    IOT_51a      ICE_42 ─┼( )└[ ]│                     │( )┘( )┼─ +3V3
    IOT_50b      ICE_38 ─┼───┐   │                     │   ┌───┼─ GND
    IOT_48b      ICE_36 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOT_44b      ICE_34 ─┼───┐   │    ┌───────────┐    │   ┌───┼─ PICO_PMOD_A4       GPIO15
    IOT_43a      ICE_32 ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B4       GPIO19
    IOT_42b      ICE_31 ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A3       GPIO14
    IOT_41a      ICE_28 ─┼( )└( )│    │  RP2040   │    │( )┘( )┼─ PICO_PMOD_B3       GPIO18
                    GND ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A2       GPIO13
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

                         ┐
   GPIO0   ICE_SO        │
   GPIO1   ICE_SSN       │ FPGA programming
   GPIO2   ICE_SCK       │ interface
   GPIO3   ICE_SI        │
                         ┘
                         ┐
   GPIO4   IOT_38b       │
   GPIO5   IOT_36b       │
   GPIO6   IOB_23b       │
   GPIO7   IOB_29b       │ Pico-FPGA
   GPIO8   IOT_39a       │ bus
   GPIO9   IOT_37a       │
   GPIO10  IOB_25b_G3    │
   GPIO11  IOB_31b       │
                         ┘
                         ┐
   GPIO12  PICO_PMOD_A1  │
   GPIO13  PICO_PMOD_A2  │
   GPIO14  PICO_PMOD_A3  │
   GPIO15  PICO_PMOD_A4  │ Pico
   GPIO16  PICO_PMOD_B1  │ PMOD
   GPIO17  PICO_PMOD_B2  │
   GPIO18  PICO_PMOD_B3  │
   GPIO19  PICO_PMOD_B4  │
                         ┘

   GPIO20  SRAM_SSN

   GPIO21  IOT_46b_G0    │ ICE_CLK (FPGA Clock)

                         ┐
   GPIO22  PICO_LED_R    │
   GPIO23  PICO_LED_G    │ LED
   GPIO24  PICO_LED_B    │
                         ┘

   GPIO25  PICO_CLKOUT   │ clock PMOD

   GPIO26  ADC0/CDONE    │ ADC PMOD / ICE_DONE (FPGA status pin)

   GPIO27  ADC1/CRESET   │ ADC PMOD / ICE_RSTn (FPGA nreset pin)

   GPIO28  ADC2          │ Other ADCs
   GPIO29  ADC3          │
                         ┘

iCE40 pinout
------------
