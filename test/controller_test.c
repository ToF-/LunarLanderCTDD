#include "unity_fixture.h"
#include "controller.h"
#include "mock_console.h"

TEST_GROUP(Controller);

TEST_SETUP(Controller)
{
}

TEST_TEAR_DOWN(Controller)
{
}

TEST(Controller, DisplaysWhenInitialized)
{
    controller_init();
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY", last_message);
}

TEST(Controller, After3SecondsDisplaysLanderState)
{
    controller_init();
    controller_update(0, 0.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY", last_message);
    controller_update(89, 0.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("LUNAR LANDING -- READY", last_message);
    controller_update(90, 1.0, 0.0);
    TEST_ASSERT_EQUAL_STRING("HEIGHT:0050.0 -- VELOCITY:-00.5 -- FUEL:20.0", last_message);
}
