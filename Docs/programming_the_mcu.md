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
Jumper ─────> │G   ││||||||||││          │
        │( ) (┼)  O            O  ( ) ( )│
        │     BT  │            │         │
        │  ───    │            │   .───. │
        │ │   │   o            o   │   │ │
        │ '───'   │            │   '───' │
        └─────────┴────────────┴─────────┘
```

The pico-ice will then reboot into bootloader mode, and you will have a drive named RP2-PICO to which you can upload a new `firmware.uf2` file.
