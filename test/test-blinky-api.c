/*!
 * \file test-blinky-api.c
 * \date 2023-12-14
 * \authors Antonio Gelain [antonio.gelain2@gmail.com]
 *
 * \brief Unit test for the blinky api.
 */

#include "unity.h"
#include "blinky-api.h"

#define PATTERN_SIZE (3U)
#define OTHER_PATTERN_SIZE (2U)

uint16_t pattern[PATTERN_SIZE] = {
    1000, // HIGH
    1000, // LOW
    1000  // HIGH
};
uint16_t otherPattern[OTHER_PATTERN_SIZE] = { 500, 2500 };

Blinky bOnce;
Blinky bRepeat;

void setUp(void) {
    blinky_init(&bOnce, pattern, PATTERN_SIZE, false, BLINKY_HIGH);
    blinky_init(&bRepeat, pattern, PATTERN_SIZE, true, BLINKY_HIGH);
}

void tearDown(void) {
}

/*!
 * \defgroup blink_init Test blink initialization
 * @{
 */

void check_blink_initial_state(void) {
    TEST_ASSERT_EQUAL_INT(BLINKY_HIGH, bOnce.initial_state);
}
void check_blink_init_null(void) {
    Blinky *b = NULL;
    blinky_init(b, NULL, 0, false, BLINKY_HIGH);
    TEST_ASSERT_NULL(b);
}
void check_blink_enable_null(void) {
    Blinky *b = NULL;
    blinky_enable(b, false);
    TEST_ASSERT_NULL(b);
}
void check_blink_repeat_null(void) {
    Blinky *b = NULL;
    blinky_repeat(b, true);
    TEST_ASSERT_NULL(b);
}
void check_blink_set_pattern_null(void) {
    Blinky *b = NULL;
    blinky_set_pattern(b, NULL, 0);
    TEST_ASSERT_NULL(b);
}
void check_blink_reset_null(void) {
    Blinky *b = NULL;
    blinky_reset(b, BLINKY_HIGH);
    TEST_ASSERT_NULL(b);
}
void check_blink_routine_null(void) {
    Blinky *b = NULL;
    blinky_routine(b, 300);
    TEST_ASSERT_NULL(b);
}

/*! @} */

/*!
 * \defgroup blink_enable Test blink enable behavior
 * @{
 */

void check_blink_enabled(void) {
    blinky_enable(&bOnce, true);
    TEST_ASSERT_TRUE(bOnce.enable);
}
void check_blink_disabled(void) {
    blinky_enable(&bOnce, false);
    TEST_ASSERT_FALSE(bOnce.enable);
}

/*! @} */

/*!
 * \defgroup blink_repeat Test blink repeat behavior
 * @{
 */

void check_blink_repeated(void) {
    blinky_repeat(&bOnce, true);
    TEST_ASSERT_TRUE(bOnce.repeat);
}
void check_blink_once(void) {
    blinky_repeat(&bOnce, false);
    TEST_ASSERT_FALSE(bOnce.repeat);
}

/*! @} */

/*!
 * \defgroup blink_set_pattern Test blink pattern modification
 * @{
 */

void check_blink_set_pattern_size(void) {
    blinky_set_pattern(&bOnce, otherPattern, OTHER_PATTERN_SIZE);
    TEST_ASSERT_EQUAL_UINT8(OTHER_PATTERN_SIZE, bOnce.size);
}
void check_blink_set_pattern_data(void) {
    blinky_set_pattern(&bOnce, otherPattern, OTHER_PATTERN_SIZE);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(otherPattern, bOnce.pattern, OTHER_PATTERN_SIZE);
}

/*! @} */

/*!
 * \defgroup blink_reset Test blink reset behavior
 * @{
 */

void check_blink_reset_time(void) {
    blinky_reset(&bOnce, BLINKY_LOW);
    TEST_ASSERT_EQUAL_UINT32(bOnce.t, 0U);
}
void check_blink_reset_index(void) {
    blinky_reset(&bOnce, BLINKY_LOW);
    TEST_ASSERT_EQUAL_UINT8(bOnce.index, 0U);
}
void check_blink_reset_state(void) {
    blinky_reset(&bOnce, BLINKY_LOW);
    TEST_ASSERT_EQUAL_INT(bOnce.state, BLINKY_LOW);
}
void check_blink_reset_enable(void) {
    blinky_reset(&bOnce, BLINKY_LOW);
    TEST_ASSERT_TRUE(bOnce.enable);
}

/*! @} */

/*!
 * \defgroup blink_routine Test blink routine
 * @{
 */

void check_blink_routine_with_null_handler(void) {
    TEST_ASSERT_EQUAL_INT(BLINKY_LOW, blinky_routine(NULL, 0));
}
void check_blink_routine_with_null_pattern(void) {
    bOnce.pattern = NULL;
    TEST_ASSERT_EQUAL_INT(BLINKY_LOW, blinky_routine(&bOnce, 0));
}
void check_blink_routine_when_disabled(void) {
    bOnce.enable = false;
    bOnce.state = BLINKY_LOW;
    TEST_ASSERT_EQUAL_INT(BLINKY_LOW, blinky_routine(&bOnce, 0));
}
void check_blink_routine_start_high(void) {
    TEST_ASSERT_EQUAL_INT(BLINKY_HIGH, blinky_routine(&bOnce, 0));
}
void check_blink_routine_change_state(void) {
    TEST_ASSERT_EQUAL_INT(BLINKY_HIGH, blinky_routine(&bOnce, 500));
    TEST_ASSERT_EQUAL_INT(BLINKY_LOW, blinky_routine(&bOnce, 1500));
}
void check_blink_routine_runned_once(void) {
    bOnce.index = 2;
    blinky_routine(&bOnce, 999);
    TEST_ASSERT_TRUE(bOnce.enable);
    blinky_routine(&bOnce, 1001);
    TEST_ASSERT_FALSE(bOnce.enable);
}
void check_blink_routine_repeated_state(void) {
    bRepeat.index = 2;
    TEST_ASSERT_EQUAL_INT(BLINKY_HIGH, blinky_routine(&bRepeat, 999));
    TEST_ASSERT_EQUAL_INT(bRepeat.initial_state, blinky_routine(&bRepeat, 1001));
}
void check_blink_routine_repeated_enable(void) {
    bRepeat.index = 2;
    blinky_routine(&bRepeat, 1001);
    TEST_ASSERT_TRUE(bRepeat.enable);
}
void check_blink_routine_repeated_index(void) {
    bRepeat.index = 2;
    blinky_routine(&bRepeat, 1001);
    TEST_ASSERT_EQUAL_UINT8(0, bRepeat.index);
}

/*! @} */

int main() {
    UNITY_BEGIN();

    /*!
     * \addtogroup blink_init Run test for blink initialization
     * @{
     */

    RUN_TEST(check_blink_initial_state);
    RUN_TEST(check_blink_init_null);
    RUN_TEST(check_blink_enable_null);
    RUN_TEST(check_blink_repeat_null);
    RUN_TEST(check_blink_set_pattern_null);
    RUN_TEST(check_blink_reset_null);
    RUN_TEST(check_blink_routine_null);

    /*! @} */

    /*! 
     * \addtogroup blink_enable Run test for blink enable behavior
     * @{
     */

    RUN_TEST(check_blink_enabled);
    RUN_TEST(check_blink_disabled);

    /*! @} */

    /*! 
     * \addtogroup blink_repeat Run test for blink repeat behavior
     * @{
     */

    RUN_TEST(check_blink_repeated);
    RUN_TEST(check_blink_once);

    /*! @} */

    /*! 
     * \addtogroup blink_set_pattern Run test for blink pattern modification
     * @{
     */

    RUN_TEST(check_blink_set_pattern_size);
    RUN_TEST(check_blink_set_pattern_data);

    /*! @} */

    /*! 
     * \addtogroup blink_reset Run test for blink reset behavior
     * @{
     */

    RUN_TEST(check_blink_reset_time);
    RUN_TEST(check_blink_reset_index);
    RUN_TEST(check_blink_reset_state);
    RUN_TEST(check_blink_reset_enable);

    /*! @} */

    /*! 
     * \addtogroup blink_routine Run test for blink routine
     * @{
     */

    RUN_TEST(check_blink_routine_with_null_handler);
    RUN_TEST(check_blink_routine_with_null_pattern);
    RUN_TEST(check_blink_routine_when_disabled);
    RUN_TEST(check_blink_routine_start_high);
    RUN_TEST(check_blink_routine_change_state);
    RUN_TEST(check_blink_routine_runned_once);
    RUN_TEST(check_blink_routine_repeated_state);
    RUN_TEST(check_blink_routine_repeated_enable);
    RUN_TEST(check_blink_routine_repeated_index);

    /*! @} */

    UNITY_END();
}
