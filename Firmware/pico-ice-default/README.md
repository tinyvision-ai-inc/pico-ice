# pico_usb_uart

In addition to the main USB-UART interface, used for the standard I/O (as used by `<stdio.h>`) (#0),
a second USB-UART (#1) interface is created:

- mirrors all input from the USB-UART to the FPGA as UART data,
- mirrors back all UART data from the FPGA to the USB-UART

Any shared I/O pins can be used. In this example, pins 0 and 1 are used.
