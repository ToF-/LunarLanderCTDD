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

TEST(Trajectory, StateAfter1SecondUpdateWithBurnRate0)
{
    LANDER lander;
    lander_initialize(&lander);
    lander_update(&lander, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_HEIGHT, lander.height);
    TEST_ASSERT_EQUAL_FLOAT(-GRAVITY, lander.velocity);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_FUEL, lander.fuel);
}
TEST(Trajectory, StateAfter2UpdatesWithBurnRate0)
{
    LANDER lander;
    lander_initialize(&lander);
    lander_update(&lander, 1.0, 0.0);
    lander_update(&lander, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_HEIGHT-GRAVITY, lander.height);
    TEST_ASSERT_EQUAL_FLOAT(-GRAVITY*2, lander.velocity);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_FUEL, lander.fuel);
}
