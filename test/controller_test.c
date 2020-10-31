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
