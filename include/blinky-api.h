/*!
 * \file blinky-api.h
 * \date 2025-03-22
 * \authors Antonio Gelain [antonio.gelain2@gmail.com]
 *      Alessandro Bridi [ale.bridi15@gmail.com]
 *
 * \brief API's of Blinky library.
 */

#ifndef BLINKY_API_H
#define BLINKY_API_H

#include "blinky.h"

/*!
 * \brief Initialize the blink handler structure.
 *
 * \param[in] b The blinky handler.
 * \param[in] pattern A pointer to the pattern to execute.
 * \param[in] size The length of the pattern.
 * \param[in] repeat Wheter to repeat the patter or run only once.
 * \param[in] state The initial state of the led.
 */
void blinky_init(
    Blinky *b,
    uint16_t *pattern,
    uint8_t size,
    bool repeat,
    BlinkyState state);

/*!
 * \brief Enable or disable blinking.
 *
 * \param[in] b The blinky handler.
 * \param[in] enabled True to enable blinky, false to disable.
 */
void blinky_enable(Blinky *b, bool enabled);

/*!
 * \brief Enable or disable pattern repetition.
 * 
 * \param[in] b The blinky handler.
 * \param[in] repeat True to repeat, false to run once.
 */
void blinky_repeat(Blinky *b, bool repeat);

/*!
 * \brief Set a new patter to execute.
 *
 * \param[in] b The blinky handler.
 * \param[in] pattern The new pattern to set.
 * \param[in] size The length of the pattern.
 */
void blinky_set_pattern(Blinky *b, uint16_t *pattern, uint8_t size);

/*!
 * \brief Re-enable and reset blinker.
 * \details The repeat option does not change.
 *
 * \param[in] b The blinky handler.
 * \param[in] state The inital state of the led.
 */
void blinky_reset(Blinky *b, BlinkyState state);

/*!
 * \brief Routine to check the state of the led.
 *
 * \param[in] b The blinky handler.
 * \param[in] t The current time.
 * \return BlinkyState The current state of the led.
 */
BlinkyState blinky_routine(Blinky *b, uint32_t t);

#endif // BLINKY_API_H
