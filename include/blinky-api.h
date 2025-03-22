/**
 * @file blinky-api.h
 * @brief API's of Blinky library
 *
 * @date 22 Mar 2025
 * @author Alessandro Bridi [ale.bridi15@gmail.com]
 */

#ifndef BLINKY_API_H
#define BLINKY_API_H

#include "blinky.h"

/**
 * @brief Initialize blink
 *
 * @param b The blinky handler
 * @param pattern A pointer to the pattern to execute
 * @param size The length of the pattern
 * @param repeat Wheter to repeat the patter or run only once
 * @param state The initial state of the led
 */
void blinky_init(
    Blinky *b,
    uint16_t *pattern,
    uint8_t size,
    bool repeat,
    BlinkyState state);

/**
 * @brief Enable or disable blinking
 *
 * @param b The blinky handler
 * @param enabled True to enable blinky, false to disable
 */
void blinky_enable(Blinky *b, bool enabled);

/**
 * @brief Enable or disable pattern repetition
 * 
 * @param b The blinky handler
 * @param repeat True to repeat, false to run once
 */
void blinky_repeat(Blinky *b, bool repeat);

/**
 * @brief Set a new patter to execute
 *
 * @param b The blinky handler
 * @param pattern The new pattern to set
 * @param size The length of the pattern
 */
void blinky_set_pattern(Blinky *b, uint16_t *pattern, uint8_t size);

/**
 * @brief Re-enable and reset blinker
 * @details The repeat option does not change
 *
 * @param b The blinky handler
 * @param state The inital state of the led
 */
void blinky_reset(Blinky *b, BlinkyState state);

/**
 * @brief Routine to check the state of the led
 *
 * @param b The blinky handler
 * @param t The current time
 * @return BlinkyState The current state of the led
 */
BlinkyState blinky_routine(Blinky *b, uint32_t t);

#endif // BLINKY_API_H
