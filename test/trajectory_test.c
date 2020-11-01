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
TEST(Trajectory, StateAfter2UpdatesWithBurnRate1)
{
    LANDER lander;
    lander_initialize(&lander);
    lander_update(&lander, 1.0, 1.0);
    lander_update(&lander, 1.0, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_HEIGHT+0.5, lander.height);
    TEST_ASSERT_EQUAL_FLOAT(1.0, lander.velocity);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_FUEL-2.0, lander.fuel);
}
TEST(Trajectory, StatusWhenHeightIsZeroAndSafeVelocity)
{
    LANDER lander;
    lander_initialize(&lander);
    TEST_ASSERT_EQUAL(IN_FLIGHT, lander_status(lander));
    lander.height = 0.0;
    lander.velocity = -0.5;
    TEST_ASSERT_EQUAL(LANDED, lander_status(lander));
}
TEST(Trajectory, StatusWhenHeightIsZeroAndUnsafeVelocity)
{
    LANDER lander;
    lander_initialize(&lander);
    lander.height = 0.0;
    lander.velocity = -1.5;
    TEST_ASSERT_EQUAL(CRASHED, lander_status(lander));
}
TEST(Trajectory, AfterLandingOrCrashingLanderCantUpdate)
{
    LANDER lander;
    lander_initialize(&lander);
    lander.height = 0.0;
    lander.velocity = -0.5;
    TEST_ASSERT_EQUAL(LANDED, lander_status(lander));
    float height = lander.height;
    float velocity = lander.velocity;
    float fuel = lander.fuel;
    lander_update(&lander, 2.0, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(height, lander.height);
    TEST_ASSERT_EQUAL_FLOAT(velocity, lander.velocity);
    TEST_ASSERT_EQUAL_FLOAT(fuel, lander.fuel);
}
TEST(Trajectory, WhenOutOfFuelBurnRateFallsToZeroWhenUpdating)
{
    LANDER lander;
    lander_initialize(&lander);
    lander.fuel = 0;
    lander_update(&lander, 1.0, 1.0);
    lander_update(&lander, 1.0, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(INITIAL_HEIGHT-GRAVITY, lander.height);
}
