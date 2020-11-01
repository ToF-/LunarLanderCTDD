#include "unity_fixture.h"
#include "trajectory.h"
#include "mock_console.h"

TEST_GROUP(Trajectory);

TEST_SETUP(Trajectory)
{
}

TEST_TEAR_DOWN(Trajectory)
{
}

TEST(Trajectory, InitialState)
{
    LANDER lander;
    lander_initialize(&lander);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_HEIGHT, lander.height);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_VELOCITY, lander.velocity);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_FUEL, lander.fuel);
}

