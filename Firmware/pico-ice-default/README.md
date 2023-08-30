# Default Firmware

Downloads: [releases](https://github.com/tinyvision-ai-inc/pico-ice/releases/)

- A first USB-UART (#0) is used for the logs, although currently nothing is printed.

- A second USB-UART (#1) interface is used for mirroring everything between
  this USB interface UART TX on RP0 with ICE27, UART RX on RP1 with ICE25.

- A 12 MHz clock is exported from the RP2040 pin 24 toward the iCE40 pin 35.

- An USB DFU interface allows programming through dfu-utils.

- An USB MSC interface allows programming with UF2.

See the [documentation](https://pico-ice.tinyvision.ai/) for how to use them.
