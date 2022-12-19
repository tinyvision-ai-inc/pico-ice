`ice_fpga_flash.h`
------------------
High-level interface for flash I/O.
All these functions act on the on-board flash chip.
For a generic flash memory I/O, you can see the low-level [`ice_smem.h`](ice_smem.md)

### `#define ICE_FLASH_PAGE_SIZE`

The size of the flash

### `void ice_flash_init(void)`

Initialise the SPI1 peripheral, dedicated to flashing the FPGA.

### `void ice_flash_deinit(void)`

Release the GPIO used for the FPGA flash so the FPGA can use them

### `void static ice_flash_wait(void)`

### `void ice_flash_read(uint32_t addr, uint8_t *buf, size_t sz)`

Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.
\param addr The address at which the data is read.
\param buf The buffer onto which the data read is stored.
\param sz The size of ``buf``.

### `void ice_flash_erase_sector(uint32_t addr)`

Erase a sector of the flash chip at the given address.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.
\param addr The beginning of the sector

### `void ice_flash_program_page(uint32_t addr, uint8_t const page[ICE_FLASH_PAGE_SIZE])`

Program a page of the flash chip at the given address.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.
\param addr The address at which the data is written.
\param page The buffer holding the data to be sent to the flash chip, of size @ref ICE_FLASH_PAGE_SIZE.

### `void ice_flash_erase_chip(void)`

Send a command to erase the whole chip.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.

### `void ice_flash_wakeup(void)`

Send a command to wakeup the chip.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.

### `void ice_flash_sleep(void)`

Send a command to put the chip to sleep.
\param spi The SPI interface of the RP2040 to use.
\param pin The CS GPIO pin of the RP2040 to use.

### `void ice_flash_enable_write(void)`

