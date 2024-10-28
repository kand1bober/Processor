#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"

int main()
{
    //=====OPEN FILE AND CREATE PROCESSOR====
    struct File_proc file = {};
    struct SPU proc = {};
    STACK_CTOR_CALL(&proc.stack, START_CAPACITY);
    InputFileCode(&file, &proc);

    //=======FILLING STRUCTURE OF PROC========
    proc.code = file.buffer;
    proc.size_of_code = file.head.size_of_code;
    proc.IP = 0;
    
    double* regs_buffer = (double*)calloc( 3, sizeof(double) );
    proc.regs = regs_buffer;


    RamCtor( &proc.memory );


    //============CHECK===========================
    for( uint32_t i = 0; i < proc.size_of_code; i++)
    {
        printf("%10u\n", *(unsigned char*)(proc.code + i) );
    }
    printf("\n");
    //============================================
    

    Run( &proc );


    free( proc.memory.ram );
    free( proc.code );
    free( proc.regs );

    return 0;   
}

