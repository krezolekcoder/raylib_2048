#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(test_2048_core)
{

    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_left);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_right);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_up);
    RUN_TEST_CASE(test_2048_core, core_test_movement_score_merging_down);
    RUN_TEST_CASE(test_2048_core, core_test_movement_possibility_left_right);
    RUN_TEST_CASE(test_2048_core, core_test_movement_possibility_up_down);
}
