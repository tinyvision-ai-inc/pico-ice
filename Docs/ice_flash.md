---
title: ice_flash.h
layout: default
parent: pico-ice-sdk
---

# `ice_flash.h`

High-level interface for flash I/O.
All these functions act on the on-board flash chip.
For a generic flash memory I/O, you can see the low-level [`ice_smem.h`](ice_smem.html)

---

## `ICE_FLASH_PAGE_SIZE`

The size of the flash

---

## `void ice_flash_init(void)`

Initialise the SPI1 peripheral, dedicated to flashing the FPGA.

---

## `void ice_flash_read(uint32_t addr, uint8_t *data, size_t data_size)`

* `addr` - The address at which the data is read.
* `data` - The buffer onto which the data read is stored.
* `data_size` - The size of `buf`.

Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.

---

## `void ice_flash_erase_sector(uint32_t addr)`

* `addr` - The beginning of the sector

Erase a sector of the flash chip at the given address.

---

## `void ice_flash_program_page(uint32_t addr, uint8_t const data[ICE_FLASH_PAGE_SIZE])`

* `addr` - The address at which the data is written.
* `data` - The buffer holding the data to be sent to the flash chip, of size @ref ICE_FLASH_PAGE_SIZE.

Program a page of the flash chip at the given address.

---

## `void ice_flash_erase_chip(void)`

Send a command to erase the whole chip.

---

## `void ice_flash_wakeup(void)`

Send a command to wakeup the chip.

---

## `void ice_flash_sleep(void)`

Send a command to put the chip to sleep.
