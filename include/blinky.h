/*!
 * \file blinky.h
 * \date 2023-12-14
 * \authors Antonio Gelain [antonio.gelain2@gmail.com]
 *      Alessandro Bridi [ale.bridi15@gmail.com]
 *
 * \brief Blink a digital led following a given pattern
 *      without using timers or blocking code.
 */

#ifndef BLINKY_H
#define BLINKY_H

#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

/*!
 * \brief Possible blinker states.
 */
typedef enum {
    BLINKY_LOW = 0,
    BLINKY_HIGH
} BlinkyState;

/*!
 * !!! GO, SLINKY GO !!!
 *
 * \attention Do not reorder elements, with this order the size occupied by the
 *      struct is the smallest possible.
 *      This is due to allignment of the struct bytes.
 * 
 * \details The time unit of measurement is dictated by the time passed to the
 *      functions (usually milliseconds).
 *
 * \struct Blinky
 * \var uint16_t *pattern An array of numbers representing the amount of time
 *      before the led changes status.
 * \var uint32_t t Last routine call timestamp.
 * \var uint8_t index The index of the current pattern value.
 * \var uint8_t size The number of elements in the pattern.
 * \var BlinkyState initial_state The initial state of the led.
 * \var BlinkyState state The current state of the led.
 * \var enable Enable or disable blinking.
 * \var repeat Run once or repeat.
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
