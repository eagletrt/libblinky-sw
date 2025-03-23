#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h> // For usleep

#include "blinky-api.h"

int main() {
    Blinky blinker;
    uint16_t pattern[] = {100, 100}; // Example pattern: 100 ms on, 100 ms off
    uint8_t size = 2;

    blinky_init(&blinker, pattern, size, true, BLINKY_LOW);
    blinky_enable(&blinker, true);

    uint32_t start_time = 0;
    uint32_t elapsed_time = 0;

    while (elapsed_time < 5000) { // Run for 5 seconds
        BlinkyState state = blinky_routine(&blinker, elapsed_time);
        printf("Time: %d ms, LED State: %s\n", elapsed_time, state == BLINKY_HIGH ? "ON" : "OFF");

        usleep(200 * 1000); // Sleep for 200 ms
        elapsed_time += 200;
    }

    blinky_enable(&blinker, false); // Disable after 5 seconds
    return 0;
}
