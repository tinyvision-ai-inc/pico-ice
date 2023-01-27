---
title: Programming the MCU
layout: default
nav_order: 2
parent: pico-ice
---

# Programming the RP2040 MCU

The pico-ice firmware offers an USB drive to which upload an UF2 file with a FPGA bitstream.

The RP2040 MCU also has its own independent UF2 file upload mechanism for uploading an UF2 file as part of the RP2040 bootloader in ROM.

To upgrade or change the firmware of the RP2040, you need to switch to that RP2040 UF2 bootloader mode instead of the FPGA UF2 mode.
You can do that by connecting a jumper between the `BT` pin a `Gnd` pin, then press the `RESET` button:

To upload a _new_ firmware image on the PR2040 (the "pico" part of "pico-ice"):

**Step 1:** Connect the `USB_BOOT` pin to ground.

{: .lh-0 }
```
        :          :          :          :
        │( ) ( )   │          │   ( ) ( )│
        │          └──────────┘          │
        │( ) ( )                  ( ) ( )│
        │                                │
        │( ) ( )  ┌────┐          ( ) ( )│
        │        '│/''\│'                │
        │( ) ( ) .│\__/│.         ( ) ( )│
        │         └────┘                 │
        │( ) (┼)                  ( ) ( )│
Jumper ─────> │G   ││||||||||││          │
        │( ) (┼)  O            O  ( ) ( )│
        │     BT  │            │         │
        │  ───    │            │   .───. │
        │ │   │   o            o   │   │ │
        │ '───'   │            │   '───' │
        └─────────┴────────────┴─────────┘
```

**Step 2:** Press and release the "RESET" button.

{: .lh-0 }
```
        :          :          :          :
        │( ) ( )   │          │   ( ) ( )│
        │          └──────────┘          │
        │( ) ( )                  ( ) ( )│
        │                                │
        │( ) ( )  ┌────┐          ( ) ( )│
        │        '│/''\│'<─ RESET        │
        │( ) ( ) .│\__/│.         ( ) ( )│
        │         └────┘                 │
        │( ) (┼)                  ( ) ( )│
        │     │G   ││||||||||││          │
        │( ) (┼)  O            O  ( ) ( )│
        │     BT  │            │         │
        │  ───    │            │   .───. │
        │ │   │   o            o   │   │ │
        │ '───'   │            │   '───' │
        └─────────┴────────────┴─────────┘
```

**Step 3:** Look for an USB drive named `RP2` and mount it, open it, and check that there are only 2 files in it: `INFO.HTML` and `INFO_UF2.TXT`.
If you also have an `CURRENT.UF2`, this means you found the FPGA flashing interface, and need to retry steps 1 and 2.

**Step 4:** Copy the `firmware.uf2` file you just built onto the USB drive.

**Step 5:** Eject the USB drive.

At this step, the firmware should be uploaded and running.
You can remove the jumper for normal use.
