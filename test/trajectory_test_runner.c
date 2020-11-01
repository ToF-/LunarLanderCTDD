#include "unity_fixture.h"

TEST_GROUP_RUNNER(Trajectory)
{
    RUN_TEST_CASE(Trajectory, InitialState);
    RUN_TEST_CASE(Trajectory, StateAfter1SecondUpdateWithBurnRate0);
    RUN_TEST_CASE(Trajectory, StateAfter2UpdatesWithBurnRate0);
    RUN_TEST_CASE(Trajectory, StateAfter2UpdatesWithBurnRate1);
    RUN_TEST_CASE(Trajectory, StatusWhenHeightIsZeroAndSafeVelocity);
    RUN_TEST_CASE(Trajectory, StatusWhenHeightIsZeroAndUnsafeVelocity);
    RUN_TEST_CASE(Trajectory, AfterLandingOrCrashingLanderCantUpdate);
}
