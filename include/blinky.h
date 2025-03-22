/**
 * @file blinky.h
 * @brief Blink a digital led following a given pattern
 * without using timers or blocking code
 *
 * @date 14 Dec 2023
 * @author Antonio Gelain [antonio.gelain@studenti.unitn.it]
 */

#ifndef BLINKY_H
#define BLINKY_H

#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    BLINKY_LOW = 0,
    BLINKY_HIGH
} BlinkyState;

/**
 * !!! GO, SLINKY GO !!!
 *
 * @attention Do not reorder elements, with this order
 * the size occupied by the struct is the smallest possible.
 * This is due to allignment of the struct bytes
 * 
 * @detail The time unit of measurement is dictated by the time passed to the functions (usually milliseconds)
 *
 * @param pattern An array of numbers representing the amount of time the led
 *        should remain in the current state.
 *        The state of the led starts as high and it toggles for every value of the array
 * @param t Last routine call timestamp
 * @param index The index of the current pattern value
 * @param size The number of elements in the pattern
 * @param state The current state of the led
 * @param enable Enable or disable blinking
 * @param repeat Run once or repeat
 */
typedef struct {
    uint16_t *pattern;
    uint32_t t;
    uint8_t index;
    uint8_t size;
    BlinkyState initial_state : 1;
    BlinkyState state : 1;
    bool enable : 1;
    bool repeat : 1;
} Blinky;


#endif // BLINKY_H
