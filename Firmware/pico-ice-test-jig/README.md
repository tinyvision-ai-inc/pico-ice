# Automated Testing of the pico-ice

This firmware is meant for testing all connections of the board with a rig as described below.

## Test process

1. load the firmware.uf2 onto the RP2040 (drag-and-drop)
2. load the bitstream.bin onto the iCE40 (dfu-util)
3. reset the board (SW1)
4. press the button to start the test outside of the jig (SW2), it should turn blue
5. put the board onto the jig
5. press the button to start the test inside of the jig (SW2), it should turn green

## Color code

- GREEN boards passed the test, can be loaded with a blinky.
- RED boards need troubleshooting, and USB UART has the full log detail
- BLINKING boards are ready to be packaged and shipped.

## Test jig

- There are horizontal (`─`) physical connections made with wires, except around `ICE_12` and `ICE_13` that are instead connected with each other vertically (`│`).
- The vertical connections (`:`) and long connections (`:...`) are made internally by the FPGA.

Together, these connecitons are building a test chain on the FPGA, whose input is controlled by the RP2040 which performs tests and report with the LED color.

```
    ┌────────────────────────────────┐
    │                                │
    │                                │
  ..│............................... │
  : │                              : │
ICE_12█ X █              ICE_16█───█ICE_14
    │ │                        :     │
ICE_13█ X █              ICE_17█───█ICE_15
  : ├───────┐                ┌─────:─┤
  : │ █ X █ │            ICE_27█───█ICE_26
  : │       │                │ :     │     
  : │ █ X █ │            ICE_25█───█ICE_23
  : │       │                │     : │     
ICE_28█───█ICE_31        ICE_21█───█ICE_20 <── TEST_CHAIN_IN
    │     : │                │ :     │      
ICE_32█───█ICE_34        ICE_19█───█ICE_18 ──> TEST_CHAIN_OUT
    │ :     │                │       │ :   
ICE_36█───█ICE_38            │ █ X █ │ :   
    │     : │                │       │ :   
ICE_42█───█ICE_43            │ █ X █ │ :   
    ├─:─────┘                └───────┤ :   
ICE_37█───█ICE_35        GPIO26█───█GPIO15
    │     :                    :     │
ICE_11█───█ICE_6         GPIO28█───█GPIO13
    │ :                            : │
ICE_10█───█ICE_9         GPIO29█───█GPIO12
    ├───────┐ :              ┌─:─────┤
    │ █ X █ │ :          GPIO16█───█GPIO20
    │       │ :              │     : │
    │ █ X █ │ :          GPIO17█───█GPIO21
    │       │ :              │ :     │
ICE_44█───█ICE_45        GPIO18█───█GPIO22
    │ :     │                │     : │
ICE_46█───█ICE_47        GPIO19█───█GPIO23
    │     : │              : │       │
ICE_48█───█ICE_2           : │ █ X █ │
    │ :     │              : │       │
 ICE_3█───█ICE_4...........: │ █ X █ │
    ├───────┘                └───────┤
 SWDIO█ X █                    █ X █ │
    │                                │
 SWCLK█ X █                    █ X █ │
    │          ││||||||||││          │
GPIO25█ X █   O            O   █ X █ │
    │         │            │         │
    │         │            │         │
    │         o            o         │
    │         │            │         │
    └─────────┴────────────┴─────────┘
```
