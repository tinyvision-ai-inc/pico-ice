---
title: ice_fpga.h
layout: default
parent: pico-ice-sdk
---

# `ice_fpga.h`

Low-level API for interacting with the FPGA chip.

---

## `void ice_fpga_init(uint8_t freq_mhz)`

* `freq_mhz` - Exported clock frequency in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.

Let the FPGA start and export a clock for it over `ICE_FPGA_CLOCK_PIN`.

The RP2040 exports its own crystal-based clock to the iCE40, through the dedicated [`CLOCK GPOUT0`](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) feature.

---

## `void ice_fpga_stop(void)`

Set the ICE_FPGA_CRESET_B_PIN to LOW which keeps the FPGA in reset mode.

---

## `bool ice_fpga_start(void)`

* Return `true` on success and `false` if it timeouts.

Release the stop mode if it was present, and wait that the FPGA confirms its startup with `ICE_FPGA_CDONE_PIN`.

---


