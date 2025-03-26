#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/*! Needed for usleep */
#include <unistd.h>

#include "blinky-api.h"

int main() {
    Blinky blinker;
    /*! Example pattern with the LED turning on for 100 ms and off for other 100 ms */
    uint16_t pattern[] = { 100U, 100U };
    const uint8_t size = 2U;

    blinky_init(&blinker, pattern, size, true, BLINKY_LOW);
    blinky_enable(&blinker, true);

    uint32_t elapsed_time = 0U;

    /*! Runs the blinking pattern for 5 seconds */
    while (elapsed_time < 5000U) {
        BlinkyState state = blinky_routine(&blinker, elapsed_time);
        printf("Time: %lu ms, LED State: %s\n", elapsed_time, state == BLINKY_HIGH ? "ON" : "OFF");

        /*! Wait for 200 ms */
        usleep(200 * 1000);
        elapsed_time += 200;
    }

    /*! Disable blinking pattern */
    blinky_enable(&blinker, false);
    return 0;
}
