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
enum BlinkyState {
    BLINKY_LOW = 0, /*!< The led is off. */
    BLINKY_HIGH     /*!< The led is on. */
};

/*!
 * !!! GO, SLINKY GO !!!
 *
 * \details The pattern is an array of numbers representing the amount of time, in the time unit of measurement, before the led changes status.
 *
 * \attention Do not reorder elements, with this order the size occupied by the
 *      struct is the smallest possible.
 *      This is due to allignment of the struct bytes.
 * 
 * \details The time unit of measurement is dictated by the time passed to the
 *      functions (usually milliseconds).
 */
struct Blinky {
    uint16_t *pattern;                  /*!< Array of numbers representing the amount of time before the led changes status. */
    uint32_t t;                         /*!< Last routine call timestamp. */
    uint8_t index;                      /*!< The index of the current pattern value. */
    uint8_t size;                       /*!< The number of elements in the pattern. */
    enum BlinkyState initial_state : 1; /*!< The initial state of the led. */
    enum BlinkyState state : 1;         /*!< The current state of the led. */
    bool enable : 1;                    /*!< Enable or disable blinking. */
    bool repeat : 1;                    /*!< Run once or repeat. */
};

#endif // BLINKY_H
