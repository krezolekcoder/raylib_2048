
#include "core_2048.h"
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
}

TEST(test_2048_core, core_test)
{
    game_tile_t *game_tile = core_2048_get_tile(1, 0);

    // initial tile should have score 2
    TEST_ASSERT_EQUAL(2U, game_tile->score);

    core_2048_check_key_pressed(KEY_LEFT);

    game_tile = core_2048_get_tile(0, 0);

    TEST_ASSERT_EQUAL(2U, game_tile->score);
}