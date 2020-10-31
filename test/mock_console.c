/* substitute for console functions allowing unit testing with no graphic effect */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "console.h"
#include "mock_console.h"

void console_display(char *message)
{
    strcpy(last_message, message);
}

