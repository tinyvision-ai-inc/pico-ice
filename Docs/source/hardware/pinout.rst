======
Pinout
======

. code-block::

                          ,────┬───────────────────────┬────.
                         /.───.│( ) ( ) ( ) ( ) ( ) ( )│.───.\
                        . │   ││                       ││   │ .
                        │ '───'│( ) ( ) ( ) ( ) ( ) ( )│'───' │
                        │      └─────────────────┬───┬─┘J7    │
                        │  LED3    ┌─────┐       ├SJ1┤    o   │
    IOB_8a      ICE_04 ─┼───┐───┐  │ SW2 │       └───┘┌───┌───┼─ +3V3
    IOB_9b      ICE_03 ─┼( )└[ ]│  └─────┘   LED2     │( )┘[ ]┼─ +3V3
    IOB_6a      ICE_02 ─┼───┐   │                     │   ┌───┼─ GND
    IOB_4a      ICE_48 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOB_2a      ICE_47 ─┼───┐   │                     │   ┌───┼─ ICE_19 IOB_29b    GPIO7 
    IOB_0a      ICE_46 ─┼( )└( )│                     │( )┘( )┼─ ICE_20 IOB_25b_G3 GPIO10
    IOB_5b      ICE_45 ─┼───┐   │                     │   ┌───┼─ ICE_21 IOB_23b    GPIO6 
    IOB_3b_G6   ICE_44 ─┼( )└( )│  ┌───────────┐      │( )┘( )┼─ ICE_18 IOB_31b    GPIO11
                   GND ─┼───┐   │  │           │      │   ┌───┼─ ICE_25 IOT_36b    GPIO5 
                   GND ─┼( )└( )│  │           │      │( )┘( )┼─ ICE_23 IOT_37a    GPIO9 
                  +3V3 ─┼───┐   │  │ ICE40UP5K │      │   ┌───┼─ ICE_27 IOT_38b    GPIO4 
                  +3V3 ─┼( )└( )│  │           │      │[ ]┘( )┼─ ICE_26 IOT_39a    GPIO8 
    IOB_18a     ICE_10 ─┼───┐───┤  │.          │      ├───┌───┼─ GND
    IOT_46a_G0  ICE_35 ─┼( )└[ ]│  └───────────┘      │( )┘( )┼─ NRESET            RUN
    IOB_20a     ICE_11 ─┼───┐   │             o       │   ┌───┼─ VBUS
    GPIO25 PICO_CLKOUT ─┼( )└( )│┌─┬─┐┌─┬─┐  TP1      │( )┘( )┼─ ADC2              GPIO28
    IOB_13b     ICE_06 ─┼───┐   ││SJ5││SJ6│           │   ┌───┼─ ICE_DONE_ADC0     GPIO26
    IOB_16a     ICE_09 ─┼( )└( )│└─┴─┘└─┴─┘           │[ ]┘( )┼─ ADC3              GPIO29
    IOT_49a     ICE_43 ─┼───┐───│                     ├───┌───┼─ +3V3
    IOT_51a     ICE_42 ─┼( )└[ ]│                     │( )┘( )┼─ +3V3
    IOT_50b     ICE_38 ─┼───┐   │                     │   ┌───┼─ GND
    IOT_48b     ICE_36 ─┼( )└( )│                     │( )┘( )┼─ GND
    IOT_44b     ICE_34 ─┼───┐   │    ┌───────────┐    │   ┌───┼─ PICO_PMOD_A4      GPIO15
    IOT_43a     ICE_32 ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B4      GPIO19
    IOT_42b     ICE_31 ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A3      GPIO14
    IOT_41a     ICE_28 ─┼( )└( )│    │  RP2040   │    │( )┘( )┼─ PICO_PMOD_B3      GPIO18
                   GND ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A2      GPIO13
                   GND ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B2      GPIO17
                  +3V3 ─┼───┐   │    └───────────┘    │   ┌───┼─ PICO_PMOD_A1      GPIO12
                  +3V3 ─┼( )└( )│                     │[ ]┘( )┼─ PICO_PMOD_B1      GPIO16
                   SWD ─┼───┐───│                     ├───┌───┼─ USB_BOOT
                 SWCLK ─┼[ ]└( )│ ┌────┐        LED4  │[ ]┘( )┼─ GND
                       ─┼───────┘ │SW1 │              └───────┤
                        │SWC SWD  │    │              BOOT GND│
                        │         └────┘                      │
                        │            ││ ||||||| ││            │
                        │          O               O          │
                        │          │               │          │
                        │  ───     │      USB      │    .───. │
                        . │   │    o               o    │   │ .
                         \'───'    │               │    '───'/
                          `─────────────────────────────────'

                                          TOP


RP2040 pinout
-------------


iCE40 pinout
------------


LEDs pinout
-----------


PMOD pinout
-----------


FLASH pinout
------------
