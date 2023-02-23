---
title: ice_led.h
layout: default
parent: pico-ice-sdk
---

# `ice_led.h`

Control the on-board RGB LED
They are active-low and shared with the iCE40:

* A LED will be bright if either the iCE40 or RP2040 are pulling its line low.
* A LED will be dark if none of the iCE40 or RP2040 are pulling its line low.

A line pulled high does not give consitent result, they are controlled with
high-impedance or pulled-down.

---

## `ice_led_init(void)`

Initialise the GPIO pins for use with open-drain LED control, shared with the iCE40.

---

## `void ice_led_red(bool on)`
## `void ice_led_green(bool on)`
## `void ice_led_blue(bool on)`

* `on` - sets the LED bright if true, dark if false.

Control for the individual red, green, blue LED.

---

## Troubleshooting

### The GPIO LEDs do not turn on

Unlike the Raspberry Pi Pico board, which has a green LED attached to the GPIO pin 25,
the pico-ice has three LEDs attached to the RP2040 GPIO13 (red), GPIO12 (green), GPIO15 (blue).

Moreover, the leds are "active-low", so you would need to turn their pin down for them to
be turned on.

Finally, the FPGA is also connected to these LEDs.
