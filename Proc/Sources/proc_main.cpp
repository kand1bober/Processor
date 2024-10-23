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
    printf("\n");

    //========CREATING PROCESSOR==============
    struct SPU flow = {};
    STACK_CTOR_CALL(&flow.stack, START_CAPACITY);
    flow.code = file.buffer;
    flow.size_of_code = file.head.size_of_code;
    flow.IP = 0;
    //========================================

    Run( &flow );

    free(file.buffer);

    return 0;   
}

