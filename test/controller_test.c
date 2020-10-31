#include "unity_fixture.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller)
{
}

TEST_TEAR_DOWN(Controller)
{
}

TEST(Controller, Dummy)
{
    TEST_ASSERT_EQUAL(5, 2+2);
}
