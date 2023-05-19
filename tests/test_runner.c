#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(test_2048_core)
{


    // RUN_TEST_CASE(test_2048_core, core_test_game_over_condition);
    RUN_TEST_CASE(test_2048_core, core_test_movement_left_right);
    RUN_TEST_CASE(test_2048_core, core_test_movement_up_down);
}
