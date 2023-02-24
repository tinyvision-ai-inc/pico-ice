#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"

int main(void) {
    stdio_init_all();
    ice_fpga_init(48);

    for (;;) {
        tud_task();
    }
    return 0;
}
