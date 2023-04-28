---
title: ice_sram.h
layout: default
parent: pico-ice-sdk
---

# `ice_sram.h`

Library for communicating with the on-board SRAM chip.

The SRAM chip is [APS6404L-3SQN](https://www.apmemory.com/wp-content/uploads/APM_PSRAM_E3_QSPI_APS6404L-3SQN-v2.6-KGD_PKG.pdf).

---

## `void ice_sram_init(void)`

Configure the SRAM SPI bus if not done already.

---

## `void ice_sram_get_id(uint8_t id[8])`

- `id` - buffer to which the ID is written.

Obtain the chip ID from the SRAM chip.

The format is:

- 8 bits - Manufacturer ID (MF ID) - 0x0D for AP Memory
- 8 bits - Known Good Die (KGD) - 0b01010101 if pass, 0b01011101 if fail
- 3 bits - Density EID - A code for memory size
- 45 bits - EID - the rest of the chip identifier

---

## `void ice_sram_read_async(uint32_t addr, uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context)`

- `addr` - address from which read the data.
- `data` - buffer to which save the data read.
- `data_size` - size of this buffer in bytes.
- `callback` - function called once the transfer is complete.
- `context` - argument passed to that function.

Read a buffer from the flash chip in the background, with a callback called once done.

Calling this function when any SPI transfer is in progress on this bus waits for it then starts.

---

## `void ice_sram_read_blocking(uint32_t addr, uint8_t *data, size_t data_size)`

Read a buffer from the flash chip and wait until completion.

---

## `void ice_sram_write_async(uint32_t addr, const uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context)`

- `addr` - address to which write the data.
- `data` - buffer with the data to send.
- `data_size` - size of this buffer in bytes.
- `callback` - function called once the transfer is complete.
- `context` - argument passed to that function.

Calling this function when any SPI transfer is in progress on this bus waits for it then starts.

Calling this function when a transfer is in progress waits then starts.

---

## `void ice_sram_write_blocking(uint32_t addr, const uint8_t *data, size_t data_size)`

Write a buffer to the flash chip and wait until completion.
