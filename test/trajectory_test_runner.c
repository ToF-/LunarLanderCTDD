#include "unity_fixture.h"

TEST_GROUP_RUNNER(Trajectory)
{
    RUN_TEST_CASE(Trajectory, InitialState);
    RUN_TEST_CASE(Trajectory, StateAfter1SecondUpdateWithBurnRate0);
    RUN_TEST_CASE(Trajectory, StateAfter2UpdatesWithBurnRate0);
}
