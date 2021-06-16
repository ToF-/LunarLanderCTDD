#include "unity_fixture.h"
#include "controller.h"
#include "trajectory.h"
#include "mock_console.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller)
{
    controller_init();
}

TEST_TEAR_DOWN(Controller)
{
}

TEST(Controller, DisplaysWhenInitialized)
{
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY IN 3", last_message);
}

TEST(Controller, InTheFirst3SecondsDisplaysWarningMessage)
{
    controller_update(0, 0.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY IN 3", last_message);
    controller_update(31, 0.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY IN 2", last_message);
    controller_update(61, 1.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY IN 1", last_message);
}
TEST(Controller, After3SecondsDisplaysLanderState)
{
    controller_update(0, 0.0, 0.0);
    controller_update(90, 1.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("HEIGHT:0050.0 -- VELOCITY:-00.5 -- FUEL:20.0", last_message);
}

TEST(Controller, CalculatesRelativePositionOfLander)
{
    controller_update(90, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.0, controller_last_relative_position());
    controller_update(91, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.01, controller_last_relative_position());
    controller_update(92, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.03, controller_last_relative_position());
    controller_update(93, 1.0, 0.0);
    TEST_ASSERT_EQUAL_FLOAT(0.06, controller_last_relative_position());
}

TEST(Controller, ChangesStateMessageIfCrashedOrLanded)
{
    for(int i; i<1000; i++) {
        controller_update(i, 1.0, 0.0);
    }
    TEST_ASSERT_EQUAL_STRING("STATUS:CRASHED", last_message);
}
TEST(Controller, GetLanderStatus)
{
    TEST_ASSERT_EQUAL_INT(IN_FLIGHT, controller_lander_status());
}
