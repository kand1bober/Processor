#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"

int main()
{
    struct File_code file = {};

    int* command_line = InputFileCode(&file);

    // size_t size = sizeof( command_line ) / sizeof( int );

    size_t size = ;

    Run( command_line, size);

    return 0;   
}

