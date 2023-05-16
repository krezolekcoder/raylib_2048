#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(test_2048_core)
{
    RUN_TEST_CASE(test_2048_core, core_test_simple_movement);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_left_4s);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_right);
}
