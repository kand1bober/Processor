#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"

int main()
{
    struct File_proc file = {};

    InputFileCode(&file);

    for(int i = 0; i < file.head.size_of_code; i++)
    {
        printf("%10d\n", *(file.buffer + i) );
    }
    
    // BinaryOutput( 65535 );

    // Run(file.buffer, file.head.size_of_code);

    free(file.buffer);

    return 0;   
}

