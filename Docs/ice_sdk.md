---
title: ice_sdk.h
layout: default
parent: pico-ice-sdk
---

# `ice_sdk.h`

High-level API for controlling everything supported by the SDK in one shot.


## `init_rgb_led(void)`

Initialise the GPIO pins for use 

This function is called by `ice_sdk_init()`.


## `void ice_sdk_init(void)`

Initialise the SDK with preset default.

No need to call the initialization function of each module when this is called.

You may instead call the individual functions to use alternative settings instead of the defaults.
