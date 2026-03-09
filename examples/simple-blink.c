#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "blinky-api.h"

int main() {
    struct Blinky blinker;
    /*! Example pattern with the LED turning on for 100 ms and off for other 100 ms */
    uint16_t pattern[] = { 100U, 100U };
    const uint8_t size = 2U;

    blinky_api_init(&blinker, pattern, size, true, BLINKY_LOW);
    blinky_api_enable(&blinker, true);

    uint32_t elapsed_time = 0U;

    /*! Runs the blinking pattern for 5 seconds */
    while (elapsed_time < 5000U) {
        enum BlinkyState state = blinky_api_routine(&blinker, elapsed_time);
        printf("Time: %lu ms, LED State: %s\n", elapsed_time, state == BLINKY_HIGH ? "ON" : "OFF");

        elapsed_time += 200;
    }

    /*! Disable blinking pattern */
    blinky_api_enable(&blinker, false);
    return 0;
}
