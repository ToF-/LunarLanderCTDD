#include "unity_fixture.h"

TEST_GROUP_RUNNER(Controller)
{
    RUN_TEST_CASE(Controller, DisplaysWhenInitialized);
    RUN_TEST_CASE(Controller, After3SecondsDisplaysLanderState);
    RUN_TEST_CASE(Controller, CalculatesRelativePositionOfLander);
    RUN_TEST_CASE(Controller, ChangesStateMessageIfCrashedOrLanded);
}
