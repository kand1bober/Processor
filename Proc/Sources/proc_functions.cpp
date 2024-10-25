#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"
#include "../Headers/proc_macros.h"


void BinaryCharOutput(unsigned char number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR , (unsigned)((number & (1 << i)) >> i) );
    }
    printf("\n");
}


void BinaryIntOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR, (unsigned)((number & (1 << i)) >> i) );
    }
    printf("\n");
}


ProcElem GetArgPush( char command, struct SPU* proc )
{
    ProcElem arg = 0;

    char mode = 0;
    mode = ( ( command & ~(255 >> 3) ));

    ON_DEBUG_PROC
    (
        printf(GREEN "Subtype of command, first 3 bits\n" DELETE_COLOR);
        BinaryCharOutput( mode );
    )

    if ( mode & INPUT_MASK )
    {
        ON_DEBUG_PROC( printf("standart input\n"); )
        arg = *(ProcElem*)(proc->code + proc->IP);
        proc->IP += sizeof( ProcElem );
    }
    else if ( mode & REGISTER_MASK )
    {
        ON_DEBUG_PROC( printf("register input\n"); )
        arg = proc->regs[ (unsigned int)(*(char*)(proc->code + proc->IP - kAX)) ]; //TODO: здесь будет сложнее
        proc->regs[ (unsigned int)(*(char*)(proc->code + proc->IP - kAX)) ] = 0;
        proc->IP += 1;
    }
    // else if ( mode & MEMORY_MASK )
    // {
    //     arg = proc->code[proc->IP];

    // }
    // else 
    // {
        
    // }

    // printf(RED "before: IP: %lu\n" DELETE_COLOR, proc->IP);
    // 
    // printf(RED "after: IP: %lu\n" DELETE_COLOR, proc->IP);

    return arg;
}


//===================INPUT FUNCTIONS========================

ProcElem GetArgPop( char command, struct SPU* proc )
{
    ProcElem arg = 0;

    char mode = 0;
    mode = ( ( command & ~(255 >> 3) ) );

    ON_DEBUG_PROC
    (
        printf("Subtype of command, first 3 bits\n");
        BinaryCharOutput( mode );
    )


    // if ()
    // {

    // }
    // else if ()
    // {

    // }

    proc->IP += sizeof( ProcElem );

    return arg;
}


void DoJump( char command, struct SPU* proc)
{
    uint64_t jump = 0;
    ProcElem a = STACK_POP_CALL( &proc->stack);
    ProcElem b = STACK_POP_CALL( &proc->stack);

    STACK_PUSH_CALL( &proc->stack, b);
    STACK_PUSH_CALL( &proc->stack, a);

    switch( *(proc->code + proc->IP++ ) ) 
    {
        case kJa:
        {   
            jump = *(double*)( proc->code + proc->IP );
            if (b > a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJae:
        {   
            jump = *(double*)( proc->code + proc->IP );
            if (b >= a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJb:
        {
            jump = *(double*)( proc->code + proc->IP );
            if (b < a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJbe:
        {
            jump = *(double*)( proc->code + proc->IP );
            if (b <= a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJe:
        {
            jump = *(double*)( proc->code + proc->IP );
            if (b == a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJne:
        {
            jump = *(double*)( proc->code + proc->IP );
            if (b != a)
            {
                proc->IP = jump;
            }
            else 
            {
                proc->IP += 1;
            }
            break;
        }
        case kJmp:
        {
            jump = *(double*)( proc->code + proc->IP );
            proc->IP = jump;
            break;
        }
    }
}
//=============================================================================================


//================================= MEMORY FUNCTIONS ==========================================

void RamDump( struct Ram* memory)
{
    printf(RED "Memory Demp\n" DELETE_COLOR);
    
}

//=============================================================================================