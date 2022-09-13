
--------------------
API pico-ice/flash.h
--------------------

API for communicating with flash chips: reading and writing.

.. c:macro:: FLASH_PAGE_SIZE

.. c:macro:: spi_fpga_flash

   The flash peripheral instance that is connected to the FGPA's flash chip.

.. c:macro:: ICE_FPGA_FLASH_SPI_SCK_PIN

.. c:macro:: ICE_FPGA_FLASH_SPI_TX_PIN

.. c:macro:: ICE_FPGA_FLASH_SPI_RX_PIN

.. c:macro:: ICE_FPGA_FLASH_SPI_CSN_PIN

   Pinout between the RP2040 and the FPGA's flash chip.
   These pins must be set at high-impedance/floating whenever not in use to program the flash chip,
   to not distrub the FPGA operation, in particular when the FPGA is under initialisation.
   This is handled by ``ice_flash_program()``.
   
   Each pin must be configured as SPI, except the CSN pin, to be set as a GPIO pin.

.. c:function:: void flash_read(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t *buf, size_t sz);

   Communicate to the chip over SPI and read multiple bytes at chosen address onto onto a buffer.
   
   :param spi: The SPI interface of the RP2040 to use.
   :param pin: The CS GPIO pin of the RP2040 to use.
   :param addr: The address at which the data is read.
   :param buf: The buffer onto which the data read is stored.
   :param sz: The size of ``buf``.

.. c:function:: void flash_program_page(spi_inst_t *spi, uint8_t pin, uint32_t addr, uint8_t const page[FLASH_PAGE_SIZE]);

   Program a page of the flash chip at the given address.
   
   :param spi: The SPI interface of the RP2040 to use.
   :param pin: The CS GPIO pin of the RP2040 to use.
   :param addr: The address at which the data is written.
   :param page: The buffer holding the data to be sent to the flash chip, of size ``FLASH_PAGE_SIZE``.

.. c:function:: void flash_erase_chip(spi_inst_t *spi, uint8_t pin);

   Send a command to erase the whole chip.
   
   :param spi: The SPI interface of the RP2040 to use.
   :param pin: The CS GPIO pin of the RP2040 to use.

------------------
API pico-ice/ice.h
------------------

High-level API for driving the board.
It is under heavy development and subject to change at any time!

.. c:macro:: ICE_FPGA_CLOCK_PIN

   The RP2040 pin at which a clock signal is sent, as a source for the ICE40 system clock.

.. c:function:: void ice_init_flash(void);

   Initialise the SPI1 peripheral, dedicated to flashing the FPGA.

.. c:function:: void ice_init_fpga_clock(uint8_t mhz);

   Initialise the FPGA clock at the given frequency.
   
   :param mhz: the clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.
