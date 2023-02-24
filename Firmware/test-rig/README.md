# Automated Testing of the pico-ice

This firmware is meant for testing all connections of the board with a rig as described below:

- There are horizontal (`─`) physical connections made with wires, except around `IOB_22a` and `IOB_24a` that are instead connected with each other vertically (`│`).

- The vertical connections (`:`) and long connections (`:...`) are made internally by the FPGA.

Together, these connecitons are building a test chain on the FPGA, whose input is controlled by the RP2040 which performs tests and report with the LED color:

- RED - something went wrong, check the USB serial console to see which test did fail.
- GREEN - everything fine, possible to proceed to the next step
- BLUE - activated by an user action (i.e. button)

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
