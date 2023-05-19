
#include "core_2048.h"
#include "test_helpers.h"
#include "unity/fixture/unity_fixture.h"
#include <stdint.h>
#include <stdio.h>



TEST_GROUP(test_2048_core);

TEST_SETUP(test_2048_core)
{
    test_helpers_clear_grid();
}

TEST_TEAR_DOWN(test_2048_core)
{ /* Cleanup after every test */

    test_helpers_clear_grid();
}


TEST(test_2048_core, core_test_movement_left_right)
{

    // [2 0 0 0] - simple one tile shift test
    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(1, 0, 0);
    core_2048_set_tile_score(2, 0, 0);
    core_2048_set_tile_score(3, 0, 0);

    core_2048_movement_update(MOVEMENT_RIGHT);

    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(3, 0));
    test_helpers_clear_grid();

    // // [2 2 0 4] - only one merging occuring
    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(1, 0, 2);
    core_2048_set_tile_score(2, 0, 0);
    core_2048_set_tile_score(3, 0, 4);


    core_2048_movement_update(MOVEMENT_RIGHT);

    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(3, 0));
    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(2, 0));
    test_helpers_clear_grid();

    // // [2 0 2 0]

    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(2, 0, 2);

    core_2048_movement_update(MOVEMENT_RIGHT);

    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(3, 0));
    test_helpers_clear_grid();
    // // [0 0 2 0 ]

    core_2048_set_tile_score(2, 0, 2);


    core_2048_movement_update(MOVEMENT_RIGHT);
    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(3, 0));

    test_helpers_clear_grid();

    // // MOVEMENT LEFT

    // // [0 0 0 2]

    core_2048_set_tile_score(0, 0, 0);
    core_2048_set_tile_score(1, 0, 0);
    core_2048_set_tile_score(2, 0, 0);
    core_2048_set_tile_score(3, 0, 2);


    core_2048_movement_update(MOVEMENT_LEFT);

    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(0, 0));

    test_helpers_clear_grid();

    // // [2 2 0 4] - only one merging occuring
    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(1, 0, 2);
    core_2048_set_tile_score(2, 0, 0);
    core_2048_set_tile_score(3, 0, 4);


    core_2048_movement_update(MOVEMENT_LEFT);


    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 0));
    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(1, 0));
}

TEST(test_2048_core, core_test_movement_up_down)
{
    // [2 0 0 0] - simple one tile shift test


    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(0, 1, 0);
    core_2048_set_tile_score(0, 2, 0);
    core_2048_set_tile_score(0, 3, 0);


    core_2048_movement_update(MOVEMENT_DOWN);


    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(0, 3));
    test_helpers_clear_grid();

    // // // [2 2 0 4] - only one merging occuring
    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(0, 1, 2);
    core_2048_set_tile_score(0, 2, 0);
    core_2048_set_tile_score(0, 3, 4);


    core_2048_movement_update(MOVEMENT_DOWN);

    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 3));
    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 2));
    test_helpers_clear_grid();

    // // // [2 0 2 0]

    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(0, 2, 2);

    core_2048_movement_update(MOVEMENT_DOWN);

    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 3));
    test_helpers_clear_grid();
    // // // [0 0 2 0 ]

    core_2048_set_tile_score(0, 2, 2);

    core_2048_movement_update(MOVEMENT_DOWN);
    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(0, 3));

    test_helpers_clear_grid();

    // // MOVEMENT LEFT

    // // [0 0 0 2]

    core_2048_set_tile_score(0, 0, 0);
    core_2048_set_tile_score(0, 1, 0);
    core_2048_set_tile_score(0, 2, 0);
    core_2048_set_tile_score(0, 3, 2);


    core_2048_movement_update(MOVEMENT_UP);

    TEST_ASSERT_EQUAL(2U, core_2048_get_tile_score(0, 0));

    test_helpers_clear_grid();

    // // [2 2 0 4] - only one merging occuring
    core_2048_set_tile_score(0, 0, 2);
    core_2048_set_tile_score(0, 1, 2);
    core_2048_set_tile_score(0, 2, 0);
    core_2048_set_tile_score(0, 3, 4);

    core_2048_movement_update(MOVEMENT_UP);

    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 0));
    TEST_ASSERT_EQUAL(4U, core_2048_get_tile_score(0, 1));
}

// TEST(test_2048_core, core_test_movement_score_merging_left)
// {
//     uint32_t start_score = 2U;

//     core_2048_set_tile_score(1, 0, start_score);
//     core_2048_set_tile_score(1, 1, start_score);
//     core_2048_set_tile_score(1, 2, start_score);
//     core_2048_set_tile_score(1, 3, start_score);

//     core_2048_movement_update(MOVEMENT_LEFT);

//     TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 0));
//     TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 1));
//     TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 2));
//     TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 3));

//     while (start_score < 2048U) {
//         core_2048_set_tile_score(1, 0, start_score);
//         core_2048_set_tile_score(1, 1, start_score);
//         core_2048_set_tile_score(1, 2, start_score);
//         core_2048_set_tile_score(1, 3, start_score);

//         core_2048_movement_update(MOVEMENT_LEFT);
//         start_score = start_score << 1U;

//         TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 0));
//         TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 1));
//         TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 2));
//         TEST_ASSERT_EQUAL(start_score, core_2048_get_tile_score(0, 3));
//     }
// }


// TEST(test_2048_core, core_test_game_over_condition)
// {
//     uint32_t start_score = 2U;

//     for (int y_coord = 0; y_coord < 4; y_coord++) {
//         for (int x_coord = 0; x_coord < 4; x_coord++) {

//             core_2048_set_tile_score(y_coord, x_coord, start_score);

//             start_score = start_score << 1U;
//         }
//     }

//     test_helpers_print_score_grid();

//     bool game_over_condition_met = core_2048_check_gameover_condition();

//     TEST_ASSERT_EQUAL(true, game_over_condition_met);
// }
