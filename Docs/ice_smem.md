---
title: ice_smem.h
layout: default
parent: pico-ice-sdk
---

# `ice_smem.h`

Low-level serial memory I/O library.

It is wrapping the pico-sdk calls for setting-up DMA channels and
communicate to serial memories through SPI, such as SRAM, FLASH, EEPROM...

Higher-level APIs make use of this for communication with each kind of memory.

> BUG: currently does not support multiple calls to `ice_smem_init()`,
> even with different IRQ numbers.
> Only affects the `_async` family of functions.

---

## `ICE_SMEM_FLASH_PAGE_SIZE`

The size of a memory page in bytes, used by various commands below.

---

## `void ice_smem_init(uint baudrate_hz, int irq)`

* `baudrate_hz` - Speed of the transfer in Hz, anything supported by
  [`spi_init()`](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__spi.html).
* `irq` - The IRQ number: either `DMA_IRQ_0` or `DMA_IRQ_1`, or `-1` for synchronous mode.

Initialize the serial memory

---

## `void ice_smem_await_async_completion(void)`

Wait that our own ongoing transaction completes.

---

## `bool ice_smem_is_async_complete(void)`

Return `true` when the ongoing asynchronous transfer is completed.

---

## `void ice_smem_deinit(void)`

Release hardware resources used by the `ice_smem.h` library.

---

## `void ice_smem_output_command(int cs_pin, const uint8_t* command, uint32_t command_size, const void* data, uint32_t data_size)`

* `cs_pin` - Chip select pin to use in the SPI transaction.
* `command` - Buffer of commands to send first.
* `command_size` - Size of this buffer.
* `data` - Buffer of data to send after the commands.
* `data_size` - Size of this buffer.

Send the two buffers in a single SPI transaction without using DMA.

Low-level function to use for building custom commands that write data.

---

## `void ice_smem_output_command_async(int cs_pin, const uint8_t* command, uint32_t command_size, const void* data, uint32_t data_size, void (*callback)(void *), void* context)`

* `callback` - Pointer to a function that will be executed upon completion of an SPI transfer (with DMA).
* `context` - Pointer passed to that function upon completion.

Async version of the command above.
(call `ice_mem_await_async_completion()` and `ice_smem_is_async_complete()` above),
and using DMA for transfers.

Low-level function to use for building custom commands that write data.

---

## `void ice_smem_input_command(int cs_pin, const uint8_t* command, uint32_t command_size, void* data, uint32_t data_size)`

* `cs_pin` - Chip select pin to use in the SPI transaction.
* `command` - Buffer of commands to send first.
* `command_size` - Size of this buffer.
* `data` - Buffer receiving the data read after the commands.
* `data_size` - Size of this buffer.

Send the first buffer, then receive data on the second buffer, in a single SPI transaction, using DMA.

Low-level function to use for building custom commands that read data.

---

## `void ice_smem_input_command_async(int cs_pin, const uint8_t* command, uint32_t command_size, void* data, uint32_t data_size, ice_smem_callback_t callback, void* context)`

* `callback` - Pointer to a function that will be executed upon completion of an SPI transfer (with DMA).
* `context` - Pointer passed to that function upon completion.

This is the same version as above, but not blocking
(call `ice_mem_await_async_completion()` and `ice_smem_is_async_complete()` above),
and using DMA for transfers.

Low-level function to use for building custom commands that read data.

---

## `uint8_t ice_smem_get_status(int cs_pin)`

* `cs_pin` - Chip select pin to use in the SPI transaction.

Return the serial chip status, containing information about its writable state, ongoing transaction...

---

## `void ice_smem_erase_chip(int cs_pin)`

* `cs_pin` - Chip select pin to use in the SPI transaction.

Issue a command to erase the whole chip.

---

## `void ice_smem_erase_sector(int cs_pin, uint32_t addr)`

* `cs_pin` - Chip select pin to use in the SPI transaction.
* `addr` - Address to erase. Must be a multiple of ICE_SMEM_FLASH_PAGE_SIZE.

Issue a command to erase a "sector", which is a region of `ICE_SMEM_FLASH_PAGE_SIZE` bytes.

---

## `void ice_smem_enable_write(int cs_pin)`

`cs_pin` - Chip select pin to use in the SPI transaction.

Issue a command to allow writing data to the chip.
Typically to be inserted before any command that modifies any content.

---

## `void ice_smem_disable_write(int cs_pin)`

* `cs_pin` - Chip select pin to use in the SPI transaction.

Issue a command to disallow writing data to the chip.

---

## `void ice_smem_write(int cs_pin, uint32_t addr, const void *data, uint32_t data_size)`

* `cs_pin` - Chip select pin to use in the SPI transaction.
* `addr` - Address to read from. Must be a multiple of ICE_SMEM_FLASH_PAGE_SIZE.
* `data` - Buffer of data to send after the commands.
* `data_size` - Size of this buffer.

Issue a write command, modifying the content of the flash.
See also `ice_smem_enable_write()`.

---

## `void ice_smem_write_async(int cs_pin, uint32_t dest_addr, const void *src, uint32_t size, ice_smem_callback_t callback, void *context)`

* `callback` - Pointer to a function that will be executed upon completion of an SPI transfer (with DMA).
* `context` - Pointer passed to that function upon completion.

Async version of the command above.

---

## `void ice_smem_read(int cs_pin, void *dest, uint32_t src_addr, uint32_t size)`

* `cs_pin` - Chip select pin to use in the SPI transaction.
* `addr` - Address to write at. Can be any value in range.
* `data` - Buffer of data to send after the commands.
* `data_size` - Size of this buffer.

Issue a read command, modifying the content of the flash.
See also `ice_smem_enable_write()`.

---

## `void ice_smem_read_async(int cs_pin, void *dest, uint32_t src_addr, uint32_t size, void (*callback)(void *), void *context)`

* `callback` - Pointer to a function that will be executed upon completion of an SPI transfer (with DMA).
* `context` - Pointer passed to that function upon completion.

Async version of the command above.

---

## `void ice_smem_power_off(int cs_pin)`

* `cs_pin` - Chip select pin to use in the SPI transaction.

Turn power off, taking the chip into sleep mode.
Woken-up by `ice_smem_power_on()`.

---

## `void ice_smem_power_on(int cs_pin)`

* `cs_pin` - Chip select pin to use in the SPI transaction.

Turn power on, taking the chip out of sleep mode.

---

Datasheets used as example:

* [Microchip 48L256](https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/20006237B.pdf)
* [Winbond W25Q32BV](https://www.winbond.com/resource-files/w25q32bv_revi_100413_wo_automotive.pdf)
* [Macronix MX25U4035F](https://www.macronix.com/Lists/Datasheet/Attachments/8700/MX25U4035F,%201.8V,%204Mb,%20v1.2.pdf)
