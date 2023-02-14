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
