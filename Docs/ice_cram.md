---
title: ice_cram.h
layout: default
parent: pico-ice-sdk
---

# `ice_cram.h`

Library for writing to the FPGA CRAM chip.

Work In Progress: It is implemented but needs to be debugged.

## `void ice_cram_open(void)`

Reset the iCE40 and set it to CRAM configuration mode and prepare the incoming SPI transfer.

## `void ice_cram_write(const uint8_t *buf, size_t len)`

* `buf` - pointer to bitstream data to flush to the iCE40
* `len` - size of that buffer

Send the bitstream to the iCE40 CRAM, which configures the FPGA circuitry.

## `bool ice_cram_close(void)`

Terminate the SPI transaction and prepare the FPGA to start,
waiting until it finishes booting.

Return `true` if the FPGA configuration succeeded or `false` if it timed out.
