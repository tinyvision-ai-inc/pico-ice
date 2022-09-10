======
Pinout
======

.. code-block::

                           ,────┬───────────────────────┬────.
                          /.───.│( ) ( ) ( ) ( ) ( ) ( )│.───.\
                         . │   ││                       ││   │ .
                         │ '───'│( ) ( ) ( ) ( ) ( ) ( )│'───' │
                         │      └─────────────────┬───┬─┘J7    │
                         │  LED3    ┌─────┐       ├SJ1┤    o   │
   IOB_8a         ICE_4 ─┼───┐───┐  │ SW2 │       └───┘┌───┌───┼─ +3V3      
   IOB_9b         ICE_3 ─┼( )└[ ]│  └─────┘   LED2     │( )┘[ ]┼─ +3V3
   IOB_6a         ICE_2 ─┼───┐   │                     │   ┌───┼─ GND
   IOB_4a        ICE_48 ─┼( )└( )│                     │( )┘( )┼─ GND
   IOB_2a        ICE_47 ─┼───┐   │                     │   ┌───┼─ ICE_19        GPIO7   IOB_29b
   IOB_0a        ICE_46 ─┼( )└( )│                     │( )┘( )┼─ ICE_20_G3     GPIO10  IOB_25b_G3
   IOB_5b        ICE_45 ─┼───┐   │                     │   ┌───┼─ ICE_21        GPIO6   IOB_23b
   IOB_3b_G6  ICE_44_G6 ─┼( )└( )│  ┌───────────┐      │( )┘( )┼─ ICE_18        GPIO11  IOB_31b
                    GND ─┼───┐   │  │           │      │   ┌───┼─ ICE_25        GPIO5   IOT_36b
                    GND ─┼( )└( )│  │           │      │( )┘( )┼─ ICE_23        GPIO9   IOT_37a
                   +3V3 ─┼───┐   │  │ ICE40UP5K │      │   ┌───┼─ ICE_27        GPIO4   IOT_38b
                   +3V3 ─┼( )└( )│  │           │      │[ ]┘( )┼─ ICE_26        GPIO8   IOT_39a
   IOB_18a    ICE_10|PB ─┼───┐───┤  │.          │      ├───┌───┼─ GND
   IOT_46a_G0 ICE_35_G0 ─┼( )└[ ]│  └───────────┘      │( )┘( )┼─ NRESET        RUN
   IOB_20a       ICE_11 ─┼───┐   │             o       │   ┌───┼─ VBUS
   GPIO25   PICO_CLKOUT ─┼( )└( )│┌─┬─┐┌─┬─┐  TP1      │( )┘( )┼─ ADC2          GPIO28
   IOB_13b        ICE_6 ─┼───┐   ││SJ5││SJ6│           │   ┌───┼─ ICE_DONE_ADC0 GPIO26
   IOB_16a        ICE_9 ─┼( )└( )│└─┴─┘└─┴─┘           │[ ]┘( )┼─ ADC3          GPIO29
   IOT_49a       ICE_43 ─┼───┐───│                     ├───┌───┼─ +3V3
   IOT_51a       ICE_42 ─┼( )└[ ]│                     │( )┘( )┼─ +3V3
   IOT_50b       ICE_38 ─┼───┐   │                     │   ┌───┼─ GND
   IOT_48b       ICE_36 ─┼( )└( )│                     │( )┘( )┼─ GND
   IOT_44b       ICE_34 ─┼───┐   │    ┌───────────┐    │   ┌───┼─ PICO_PMOD_A4  GPIO15
   IOT_43a       ICE_32 ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B4  GPIO19
   IOT_42b       ICE_31 ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A3  GPIO14
   IOT_41a       ICE_28 ─┼( )└( )│    │  RP2040   │    │( )┘( )┼─ PICO_PMOD_B3  GPIO18
                    GND ─┼───┐   │    │           │    │   ┌───┼─ PICO_PMOD_A2  GPIO13
                    GND ─┼( )└( )│    │           │    │( )┘( )┼─ PICO_PMOD_B2  GPIO17
                   +3V3 ─┼───┐   │    └───────────┘    │   ┌───┼─ PICO_PMOD_A1  GPIO12
                   +3V3 ─┼( )└( )│                     │[ ]┘( )┼─ PICO_PMOD_B1  GPIO16
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
