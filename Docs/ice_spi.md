---
title: ice_spi.h
layout: default
parent: pico-ice-sdk
---

# `ice_spi.h`

SPI library exclusive to the main SPI bus between the RP2040 and the various other board components,
including the iCE40 CRAM, iCE40 hardened SPI core, SRAM chip, FLASH chip.

---

## `void ice_spi_init(void)`

Configure the GPIO pins of the SPI library to high-impedance to let others access the bus,
such as the iCE40 during initial configuration.

---

## `void ice_spi_chip_select(uint8_t csn_pin, bool active_high)`

* `csn_pin` - user-selectable GPIO pin to assert (set to LOW voltage level)
* `active_high` - true for active-high chip-select pin, false for active-low

Also set the SPI TX and SCK pins to output/drive mode, and keeps the RX pin to input/high-z mode.

---

## `void ice_spi_chip_deselect(uint8_t csn_pin)`

* `csn_pin` - user-selectable GPIO pin to assert (set to LOW voltage level)

Also set the SPI TX and SCK pins back to input/high-z mode.

---

## `void ice_spi_write_async(uint8_t const *buf, size_t len, void (*callback)(volatile void *), void *context)`

* `buf` - buffer to send over SPI.
* `len` - size of that buffer.
* `callback` - function called at the end of the transfer.
* `context` - argument passed to that function.

Wait previous transfer completion if any and enqueue a new one in the background (interrupt-driven).
If `callback` is `NULL`, then nothing will be done.

---

## `void ice_spi_read_async(uint8_t tx, uint8_t *buf, size_t len, void (*callback)(volatile void *), void *context)`

* `tx` - byte to send conotinuously while readying
* `buf` - buffer to fill from SPI.
* `len` - size of that buffer.
* `callback` - function called at the end of the transfer.
* `context` - argument passed to that function.

Wait previous transfer completion if any and enqueue a new one in the background (interrupt-driven).
If `callback` is `NULL`, then nothing will be done.

---

## `bool ice_spi_is_async_complete(void)`

Return `true` if an SPI transfer is ongoing, `false` if ready to enqueue another.

---

## `void ice_spi_await_async_completion(void)`

Waits until SPI transfer completion.

---

## `void ice_spi_read_blocking(uint8_t tx, uint8_t *buf, size_t len)`

* `tx` - byte to send conotinuously while readying
* `buf` - buffer to fill from SPI.
* `len` - size of that buffer.

Blocking version of `ice_spi_read_async()`.

---

## `void ice_spi_write_blocking(uint8_t const *buf, size_t len)`

* `buf` - buffer to send over SPI.
* `len` - size of that buffer.

Blocking version of `ice_spi_write_async()`.
