
---------------------
API boards/pico_ice.h
---------------------

.. c:macro:: _BOARDS_ICE_H

Specific to pico-ice

.. c:macro:: ICE_LED_RED_PIN

   Red LED control pin of the RGB led.

.. c:macro:: ICE_LED_GREEN_PIN

   Green LED control pin of the RGB led.

.. c:macro:: ICE_LED_BLUE_PIN

   Blue LED control pin of the RGB led.

   Pinout between the RP2040 and the FPGA's UART port.

.. c:macro:: ICE_FPGA_UART_TX_PIN

.. c:macro:: ICE_FPGA_UART_RX_PIN

   Pinout between the RP2040 and the FPGA's flash chip.
   These pins must be set at high-impedance/floating whenever not in use to program the flash chip,
   to not distrub the FPGA operation, in particular when the FPGA is under initialisation.

.. c:macro:: ICE_FLASH_SPI_SCK_PIN

   Configured as SPI FUNCSEL by ``ice_init_flash()``.

.. c:macro:: ICE_FLASH_SPI_TX_PIN

   Configured as SPI FUNCSEL by ``ice_init_flash()``.

.. c:macro:: ICE_FLASH_SPI_RX_PIN

   Configured as SPI FUNCSEL by ``ice_init_flash()``.

.. c:macro:: ICE_FLASH_SPI_CSN_PIN

   It is configured as GPIO FUNCSEL by ``ice_init_flash()``,
   and controlled by the flash library.

.. c:macro:: ICE_FPGA_CLOCK_PIN

   The RP2040 pin at which a clock signal is sent, as a source for the ICE40 system clock.

.. c:macro:: ICE_FPGA_FLASH_SIZE_BYTES

   The size of the W25Q32JVSSIQ flash chip also connected to the FPGA.

.. c:macro:: TINYVISION_AI_INC_PICO_ICE

   To use for board-detection.

   UART
   ~~~~

.. c:macro:: uart_fpga

   UART interface transferring everything received over an USB UART interface (USB CDC ACM).

.. c:macro:: PICO_DEFAULT_UART

   Same as the pico-sdk: stdio_init_all() will enable this UART0.

.. c:macro:: PICO_DEFAULT_UART_TX_PIN

   Different than boards/pico.h: same physical location, different GPIO pin.

.. c:macro:: PICO_DEFAULT_UART_RX_PIN

   Different than boards/pico.h: same physical location, different GPIO pin.

   LED
   ~~~

.. c:macro:: PICO_DEFAULT_LED_PIN

   The GPIO25 used by pico-sdk is used for sending the clock over to the FPGA.
   There are three LED pins (RGB): GPIO22 (red), GPIO23 (green), GPIO24 (blue).

   I2C
   ~~~

.. c:macro:: PICO_DEFAULT_I2C

.. c:macro:: PICO_DEFAULT_I2C_SDA_PIN

.. c:macro:: PICO_DEFAULT_I2C_SCL_PIN

   SPI
   ~~~

.. c:macro:: PICO_DEFAULT_SPI

   The communication with the flash is done via SPI1,
   letting SPI0 for the user like in the pico-sdk.
   The pinout is unchanged.

.. c:macro:: PICO_DEFAULT_SPI_SCK_PIN

.. c:macro:: PICO_DEFAULT_SPI_TX_PIN

.. c:macro:: PICO_DEFAULT_SPI_RX_PIN

.. c:macro:: PICO_DEFAULT_SPI_CSN_PIN

   FLASH
   ~~~~~
   
   This is the internal flash used by the RP2040 chip,
   not the flash used by the ICE40 FPGA.

.. c:macro:: spi_fpga_flash

   The flash peripheral instance that is connected to the FGPA's flash chip.

.. c:macro:: PICO_BOOT_STAGE2_CHOOSE_W25Q080

   The pico-ice uses the same chip except with a larger size, and it also supports QSPI:
   https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/boot_stage2/boot2_w25q080.S

.. c:macro:: PICO_FLASH_SPI_CLKDIV

   The pico-ice has the same flash chip family as the pico with the same clock speed.

.. c:macro:: PICO_FLASH_SIZE_BYTES

   The flash chip is W25Q32JVSSIQ: twice larger than the pico.

.. c:macro:: PICO_SMPS_MODE_PIN

   Changed from the default pico-board to not enable it at all time (due to the RGB LED driving it up).
   Drive high to force power supply into PWM mode (lower ripple on 3V3 at light loads)
   It is the PICO_PMOD_A4 pin.

.. c:macro:: PICO_RP2040_B0_SUPPORTED

   Nearly all RP2040 chips sold on 2022 are B0 or B1 iterations, so B0 features are guaranteed to be supported.

--------------------
API pico_ice/flash.h
--------------------

Low-level API for communicating with flash chips: reading and writing.

.. c:macro:: FLASH_PAGE_SIZE

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

-------------------
API pico_ice/fpga.h
-------------------

Low-level API for interacting with the FPGA chip.

.. c:function:: void fpga_init_clock(uint8_t mhz);

   Initialise the FPGA clock at the given frequency.
   
   :param mhz: The clock speed in MHz. Valid values: 48MHz, 24MHz, 16MHz 12MHz, 8MHz, 6MHz, 4MHz, 3MHz, 2MHz, 1MHz.

.. c:function:: void fpga_init_uart(uint32_t mhz);

   Initialise the UART peripheral for communication with the FPGA, at the given baudrate.
   
   :param mhz: The baud rate speed in MHz. Can be any value supported by the pico-sdk.

------------------
API pico_ice/ice.h
------------------

High-level API for driving the board.
It is under heavy development and subject to change at any time!

.. c:function:: void ice_init_defaults(void);

   Call all functions below with default values:
   no need to call any other initialization function when this is called.

.. c:function:: void ice_init_flash(void);

   Initialise the SPI1 peripheral, dedicated to flashing the FPGA.

.. c:function:: void ice_init_usb(void);

   Initialise the TinyUSB library, enabling the UART (CDC) and
   drag-and-drop (MSC) interfaces.

.. c:function:: void ice_init_fpga(void);

   Initialise the FPGA chip and communication with it.
   This will start the FPGA.

.. c:function:: void ice_usb_task(void);

   Run all code related to USB in a non-blocking way.
   It is typically to be placed at the end of the main application loop.

-------------------
API pico_ice/priv.h
-------------------

All functions defined for internal use, not useful for using the SDK.

.. c:function:: void tud_task_cdc(void);

.. c:function:: void uf2_init(void);
