
#include "core_2048.h"
#include "test_helpers.h"
#include "unity/fixture/unity_fixture.h"
#include <stdint.h>
#include <stdio.h>



TEST_GROUP(test_2048_core);

TEST_SETUP(test_2048_core)
{
    // core_2048_tiles_init(1, 4);
}

TEST_TEAR_DOWN(test_2048_core)
{ /* Cleanup after every test */

    for (int y_coord = 0; y_coord < 4; y_coord++) {
        for (int x_coord = 0; x_coord < 4; x_coord++) {

            test_helpers_set_tile_score(y_coord, x_coord, 0);
        }
    }
}

TEST(test_2048_core, core_test_movement_score_merging_left)
{
    uint32_t start_score = 2U;

    test_helpers_set_tile_score(1, 0, start_score);
    test_helpers_set_tile_score(1, 1, start_score);
    test_helpers_set_tile_score(1, 2, start_score);
    test_helpers_set_tile_score(1, 3, start_score);

    core_2048_check_key_pressed(KEY_LEFT);

    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 0)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 1)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 2)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 3)->score);

    while (start_score < 2048U) {
        test_helpers_set_tile_score(1, 0, start_score);
        test_helpers_set_tile_score(1, 1, start_score);
        test_helpers_set_tile_score(1, 2, start_score);
        test_helpers_set_tile_score(1, 3, start_score);

        core_2048_check_key_pressed(KEY_LEFT);
        start_score = start_score << 1U;

        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 0)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 1)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 2)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 3)->score);
    }
}

TEST(test_2048_core, core_test_movement_score_merging_right)
{
    uint32_t start_score = 2U;

    test_helpers_set_tile_score(1, 0, start_score);
    test_helpers_set_tile_score(1, 1, start_score);
    test_helpers_set_tile_score(1, 2, start_score);
    test_helpers_set_tile_score(1, 3, start_score);

    core_2048_check_key_pressed(KEY_RIGHT);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 0)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 1)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 2)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 3)->score);


    while (start_score < 2048U) {
        test_helpers_set_tile_score(1, 0, start_score);
        test_helpers_set_tile_score(1, 1, start_score);
        test_helpers_set_tile_score(1, 2, start_score);
        test_helpers_set_tile_score(1, 3, start_score);

        core_2048_check_key_pressed(KEY_RIGHT);
        start_score = start_score << 1U;

        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 0)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 1)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 2)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 3)->score);
    }
}


TEST(test_2048_core, core_test_movement_score_merging_up)
{
    uint32_t start_score = 2U;

    test_helpers_set_tile_score(0, 1, start_score);
    test_helpers_set_tile_score(1, 1, start_score);
    test_helpers_set_tile_score(2, 1, start_score);
    test_helpers_set_tile_score(3, 1, start_score);

    core_2048_check_key_pressed(KEY_UP);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 0)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(1, 0)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(2, 0)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 0)->score);

    while (start_score < 2048U) {
        test_helpers_set_tile_score(0, 1, start_score);
        test_helpers_set_tile_score(1, 1, start_score);
        test_helpers_set_tile_score(2, 1, start_score);
        test_helpers_set_tile_score(3, 1, start_score);


        core_2048_check_key_pressed(KEY_UP);
        start_score = start_score << 1U;

        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 0)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(1, 0)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(2, 0)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 0)->score);
    }
}

TEST(test_2048_core, core_test_movement_score_merging_down)
{
    uint32_t start_score = 2U;

    test_helpers_set_tile_score(0, 1, start_score);
    test_helpers_set_tile_score(1, 1, start_score);
    test_helpers_set_tile_score(2, 1, start_score);
    test_helpers_set_tile_score(3, 1, start_score);

    core_2048_check_key_pressed(KEY_DOWN);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 3)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(1, 3)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(2, 3)->score);
    TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 3)->score);

    while (start_score < 2048U) {
        test_helpers_set_tile_score(0, 1, start_score);
        test_helpers_set_tile_score(1, 1, start_score);
        test_helpers_set_tile_score(2, 1, start_score);
        test_helpers_set_tile_score(3, 1, start_score);


        core_2048_check_key_pressed(KEY_DOWN);
        start_score = start_score << 1U;

        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(0, 3)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(1, 3)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(2, 3)->score);
        TEST_ASSERT_EQUAL(start_score, core_2048_get_tile(3, 3)->score);
    }
}