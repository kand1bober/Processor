#include "../Headers/library.h"
#include "../Headers/functions.h"
#include <cstdint>

int main()
{
    int command_line[] = {1, 56, 1, 54, 1, 12, 11, 21, 88, 11, 2, 2, 11, 12};

    size_t size = sizeof( command_line ) / sizeof( int );

    Run( command_line, size);

    return 0;   
}

