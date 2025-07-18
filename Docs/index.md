[Doc](http://pico-ice.tinyvision.ai/)
| [Hardware](https://github.com/tinyvision-ai-inc/pico-ice)
| [SDK](https://github.com/tinyvision-ai-inc/pico-ice-sdk)
| [Schematic](https://raw.githubusercontent.com/tinyvision-ai-inc/pico-ice/main/Board/Rev3/pico-ice.pdf)
| [Assembly](https://htmlpreview.github.io/?https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Board/Rev3/bom/ibom.html)
| [Discord](https://discord.gg/t2CzbAYeD2)

[![Elecrow](https://www.elecrow.com/media/logo/stores/1/ELECROW_LOGO.png)](https://www.elecrow.com/pico-ice-rp2040-plus-lattice-ice40up5k-fpga.html)
[![LectronZ](https://lectronz.com/static/badges/buy-it-on-lectronz-medium.png)](https://lectronz.com/stores/tinyvision-ai-store)
[![Tindie](https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-smalls.png)](https://www.tindie.com/stores/tinyvision_ai/)

The pico-ice is a small, low cost board with the Raspberry Pi Pico processor ([RP2040](https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html)) and a Lattice Semiconductor [iCE40UP5K](https://www.latticesemi.com/en/Products/FPGAandCPLD/iCE40UltraPlus) FPGA. The board features independent flash for the FPGA and RP2040, low power SSRAM, a couple of pushbuttons and a 3 color LED with _all_ FPGA and RP2040 pins brought out to easy to use 0.1" header pins (arranged as Pmod's) for fast prototyping.

![](images/pico_ice_front.jpg)
![](images/pico_ice_back.jpg)

Board Hardware Features:

* Raspberry Pi RP2040 processor
* Lattice UltraPlus ICE40UP5K FPGA with 5.3k LUTs, 1Mb SPRAM, 120Kb DPRAM, 8 Multipliers
* _ALL_ RP2040 and 32 FPGA GPIO on 0.1” headers
* 4MB SPI Flash
* 8MB low power qSPI SRAM
* RGB LED, shared between the RP2040 and FPGA
* 2 pushbuttons, 1 dedicated and 1 primarily for processor reset during development but can be repurposed for user applications when not used for reset
* On board 3.3V and 1.2V Regulators, can supply 3.3V to your project
* Open source schematic and layout using KiCAD design tools
* 4 layer board with a solid ground plane for good signal integrity

Board Firmware features:

* FPGA clock supplied by the RP2040, easy to program FPGA clock under SW control
* RP2040 can program the FPGA in various ways
* Examples for communicating to the FPGA from USB to UART or SPI
* Support for ultra low power sleeep mode: can shut down the RP2040 and FPGA while keeping the SRAM powered

![](images/pico_ice_blocks.png)

[OSHW US002140](https://certification.oshwa.org/us002140.html) | Certified open source hardware | oshwa.org/cert
