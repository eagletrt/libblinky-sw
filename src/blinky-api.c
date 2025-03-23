/*!
 * \file blinky.c
 * \date 2023-12-14
 * \authors Antonio Gelain [antonio.gelain2@gmail.com]
 *
 * \brief Blink a digital led following a given pattern
 *      without using timers or blocking code.
 */

#include "blinky.h"

void blinky_init(
    Blinky *b,
    uint16_t *pattern,
    uint8_t size,
    bool repeat,
    BlinkyState state) {
    if (b == NULL)
        return;
    b->pattern = pattern;
    b->t = 0;
    b->index = 0;
    b->size = size;
    b->initial_state = state;
    b->state = state;
    b->enable = true;
    b->repeat = repeat;
}

void blinky_enable(Blinky *b, bool enabled) {
    if (b == NULL)
        return;
    b->enable = enabled;
}

void blinky_repeat(Blinky *b, bool repeat) {
    if (b == NULL)
        return;
    b->repeat = repeat;
}

void blinky_set_pattern(Blinky *b, uint16_t *pattern, uint8_t size) {
    if (b == NULL)
        return;
    b->pattern = pattern;
    b->size = size;
}

void blinky_reset(Blinky *b, BlinkyState state) {
    if (b == NULL)
        return;
    b->t = 0;
    b->index = 0;
    b->initial_state = state;
    b->state = state;
    b->enable = true;
}

BlinkyState blinky_routine(Blinky *b, uint32_t t) {
    if (b == NULL || b->pattern == NULL)
        return BLINKY_LOW;
    if (!b->enable)
        return b->state;

    /*! Check if current status has to be changed */
    if (t - b->t >= b->pattern[b->index]) {
        b->state = !b->state;
        b->t = t;
        ++b->index;

        /*! Return to the start of the pattern if it ended */
        if (b->index >= b->size) {
            /*! Disable the blinker if repeat is not active */
            if (!b->repeat)
                b->enable = false;

            b->index = 0;
            b->state = b->initial_state;
        }
    }

    return b->state;
}
