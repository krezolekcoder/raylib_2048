
#include "unity/fixture/unity_fixture.h"
#include <stdint.h>
#include <stdio.h>



TEST_GROUP(test_2048_core);

TEST_SETUP(test_2048_core)
{
}

TEST_TEAR_DOWN(test_2048_core)
{ /* Cleanup after every test */
}

TEST(test_2048_core, core_test)
{

    TEST_ASSERT_EQUAL(1, 1);
}