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

- There are horizontal (`─`) physical connections made with wires, except around `IOB_22a` and `IOB_24a` that are instead connected with each other vertically (`│`).
- The vertical connections (`:`) and long connections (`:...`) are made internally by the FPGA.

Together, these connecitons are building a test chain on the FPGA, whose input is controlled by the RP2040 which performs tests and report with the LED color.

```
      ┌────────────────────────────────┐
      │                                │
      │                                │
    ..│.......................         │
    : │                      :         │
 IOB_22a█   █             IOB_35B█───█IOB_32A
      │ │                            : │
 IOB_24a█   █             IOB_33b█───█IOB_34a
    : ├───────┐                ┌─:─────┐     
    : │ █   █ │           IOT_38b█───█IOT_39a
    : │       │                │     : │     
    : │ █   █ │           IOT_36b█───█IOT_37a
    : │       │                │ :     │     
 IOT_41a█───█IOT_42b      IOB_23b█───█IOB_25b <── TEST_CHAIN_IN
      │     : │                │       │      
 IOT_43a█───█IOT_44b      IOB_29b█───█IOB_31b ──> TEST_CHAIN_OUT
      │ :     │              : │       │     
 IOT_48b█───█IOT_50b         : │ █   █ │     
      │     : │              : │       │     
 IOT_51a█───█IOT_49a         : │ █   █ │     
      ├─:─────┘              : └───────┤     
 IOT_45a█───█IOT_46b         :   █   █ │
      │     :                :         │
 IOB_20a█───█IOB_13b         :   █   █ │
      │ :                    :         │
 IOB_18a█───█IOB_16a         :   █   █ │
      ├───────┐ :            : ┌───────┤
      │ █   █ │ :            : │ █   █ │
      │       │ :            : │       │
      │ █   █ │ :            : │ █   █ │
      │       │ :            : │       │
  IOB_3b█───█IOB_5b          : │ █   █ │
      │ :     │              : │       │
  IOB_0a█───█IOB_2a          : │ █   █ │
      │     : │              : │       │
  IOB_4a█───█IOB_6a          : │ █   █ │
      │ :     │              : │       │
  IOB_9b█───█IOB_8a..........: │ █   █ │
      ├───────┘                └───────┤
      │ █   █                    █   █ │
      │                                │
      │ █   █                    █   █ │
      │          ││||||||||││          │
      │ █   █   O            O   █   █ │
      │         │            │         │
      │         │            │         │
      │         o            o         │
      │         │            │         │
      └─────────┴────────────┴─────────┘
```
