#include "blinky-api.h"

#define PATTERN_SIZE 2

uint16_t pattern[PATTERN_SIZE] = {
    1000,
    1000
};

int main() {
    Blinky b;
    blinky_init(&b, pattern, PATTERN_SIZE, true, BLINKY_LOW);

    // Do your things
    BlinkyState state = blinky_routine(&b, time_in_ms); // call this sometimes to get the state to set

    led_set(state);

    return 0;
}
