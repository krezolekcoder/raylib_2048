
#include "core_2048.h"
#include "test_helpers.h"
#include "unity/fixture/unity_fixture.h"
#include <stdint.h>
#include <stdio.h>



TEST_GROUP(test_2048_core);

TEST_SETUP(test_2048_core)
{
    core_2048_tiles_init(1, 4);
}

TEST_TEAR_DOWN(test_2048_core)
{ /* Cleanup after every test */

    for (int y_coord = 0; y_coord < 4; y_coord++) {
        for (int x_coord = 0; x_coord < 4; x_coord++) {

            test_helpers_set_tile_score(y_coord, x_coord, 0);
        }
    }
}

TEST(test_2048_core, core_test_simple_movement)
{
    game_tile_t *game_tile = core_2048_get_tile(1, 0);

    // initial tile should have score 2
    TEST_ASSERT_EQUAL(2U, game_tile->score);

    core_2048_check_key_pressed(KEY_LEFT);

    game_tile = core_2048_get_tile(0, 0);

    TEST_ASSERT_EQUAL(2U, game_tile->score);
}

TEST(test_2048_core, core_test_movement_score_merging)
{

    test_helpers_set_tile_score(1, 0, 2);
    test_helpers_set_tile_score(3, 0, 2);

    test_helpers_print_score_grid();

    printf("LEFT KEY PRESSED : \r\n");
    core_2048_check_key_pressed(KEY_LEFT);

    test_helpers_print_score_grid();

    game_tile_t *game_tile = core_2048_get_tile(0, 0);


    TEST_ASSERT_EQUAL(4U, game_tile->score);

    game_tile = core_2048_get_tile(0, 1);

    TEST_ASSERT_EQUAL(0U, game_tile->score);

    game_tile = core_2048_get_tile(0, 2);

    TEST_ASSERT_EQUAL(0U, game_tile->score);

    game_tile = core_2048_get_tile(0, 3);

    TEST_ASSERT_EQUAL(0U, game_tile->score);
}