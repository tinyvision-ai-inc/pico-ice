#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"

int main(void) {
    stdio_init_all();
    // [...] more setup code here

    for (;;) {
        tud_task();

        // [...] more application code here
    }
    return 0;
}
