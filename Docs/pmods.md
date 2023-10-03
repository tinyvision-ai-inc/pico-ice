---
title: pmod
layout: default
nav_order: 3
---

# Pmod

The Pmod Connection system is using a grid of 2 rows and 6 columns of pins.

It was designed by Digilent to offer something compatible with both classical jumper wires used on breadboards,
and a standardised pinout that supports multiple protocols on the same connector.

This is popular on FPGA boards as it permits them to support any protocol over
the same connector with the right pinout, rarely possible on MCUs.

This standard is documented [here](https://reference.digilentinc.com/_media/reference/pmod/pmodoledrgb/pmodoledrgb_sch.pdf).

## Pmod in the pico-ice

Here is an [example of how to solder](/getting_started.html#soldering-the-pmods) the Pmod connectors.

There are 4 Pmod connectors in the pico-ice, numbered clockwise from 1 to 4 starting from the USB connector.

- 2 connected ot the iCE40
- 1 connected to both the RP2040 and iCE40
- 1 connected to the RP2040

The pinout of the RP2040 is made to be compatible with SPI0,
with the other protocols that may be bit-banged or implemented with PIO to be pin-compatible.

For the iCE40, the pin numbers are available from
[pico_ice.pcf](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/rtl/pico_ice.pcf).

For the RP2040, the pin numbers are available from
[ice_pmod.h](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/include/ice_pmod.h).

You can then use any of the pinout declaration described
[here](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/include/pmod.h).

```
// Use the pins from their GPIO names
gpio_init(ice_pmod_3.gpio.io1);
gpio_init(ice_pmod_3.gpio.io2);
gpio_init(ice_pmod_3.gpio.io3);
gpio_init(ice_pmod_3.gpio.io4);
gpio_init(ice_pmod_3.gpio.io7);
gpio_init(ice_pmod_3.gpio.io8);
gpio_init(ice_pmod_3.gpio.io9);
gpio_init(ice_pmod_3.gpio.io10);

// Use the pins from their I²C names
gpio_init(ice_pmod_3.i2c.sda);
gpio_init(ice_pmod_3.i2c.scl);

// Use the pins from their UART names
gpio_init(ice_pmod_3.i2c.tx);
gpio_init(ice_pmod_3.i2c.rx);

// Use the pins from their SPI names
gpio_set_function(ice_pmod_3.spi.copi, FUNC_SPI);
gpio_set_function(ice_pmod_3.spi.cipo, FUNC_SPI);
gpio_set_function(ice_pmod_3.spi.clk, FUNC_SPI);

// Access the top or bottom row individually
gpio_set_function(ice_pmod_3.row.top.spi.copi, FUNC_SPI);
gpio_set_function(ice_pmod_3.row.bottom.spi.copi, FUNC_SPI);

[...]
```


## Pmod Modules

There are many Pmod vendors, and this page attempts to enumerate as many as possible.

If you have made a Pmod module, let us know and we would add it to this list!

- <https://www.infineon.com/cms/en/search.html#!term=pmod&view=products>
- <https://digilent.com/shop/boards-and-components/system-board-expansion-modules/pmods/>
- <https://www.renesas.com/us/en/software-tool/quick-connect-iot-platform>
- <https://www.tindie.com/stores/johnnywu/>
- <https://1bitsquared.com/collections/fpga>
- <https://www.tindie.com/search/?q=pmod>
- <https://lectronz.com/products/search?q=pmod>
- <https://www.aries-embedded.com/evaluation-kit/tools/pmod-extension-module>
- <https://github.com/wuxx/icesugar/tree/master/schematic>
- <https://machdyne.com/?s=pmod&post_type=product>
- <https://aliexpress.com/store/912189181/search?SearchText=pmod>
- <https://github.com/swetland/ethernet-pmod>
- <https://fpga.fm4dd.com/>
- <https://github.com/icebreaker-fpga/icebreaker-pmod>
- <https://blackmesalabs.wordpress.com/>
- <https://www.solder.party/docs/keyboard-pmod/pmod-to-qwiic-adapter/>
- <https://github.com/marcinwachowiak/pmod-pdm-microphone-array/>
- <https://github.com/apfelaudio/eurorack-pmod>
