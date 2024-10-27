#define DEBUG

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


ProcElem GetArgPush( struct SPU* proc )
{
    char command = *(char*)(proc->code + proc->IP);
    proc->IP += 1;
    char mode = ( ( command & ~(255 >> 3) ));

    ON_DEBUG_PROC
    (
        printf(GREEN "Subtype of command, first 3 bits\n" DELETE_COLOR);
        BinaryCharOutput( mode );
    )

    ProcElem arg = 0;
    uint64_t ram_addr = 0;

    if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) && (mode & INPUT_MASK) )
    {

        ram_addr = (uint64_t)( proc->regs[ *(char*)(proc->code + proc->IP ) - kAX ] );

        ON_DEBUG_PROC( uint64_t first_arg = ram_addr; )

        proc->IP += 1;
        ram_addr = (uint64_t)( *(ProcElem*)(proc->code + proc->IP));

        ON_DEBUG_PROC( uint64_t second_arg = ram_addr; )

        ON_DEBUG_PROC( printf("push from memory, from [ %lu + %lu ] \n", first_arg, second_arg); )

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);

        proc->IP += sizeof( ProcElem );
    }
    else if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) )
    {
        ram_addr = (uint64_t)( proc->regs[ *(char*)(proc->code + proc->IP) - kAX ] );

        ON_DEBUG_PROC( printf("push from memory, from register %d\n", *(char*)(proc->code + proc->IP) - kAX  ); )

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);
        proc->IP += 1;
    }
    else if( (mode & MEMORY_MASK ) && (mode & INPUT_MASK) )
    {
        ON_DEBUG_PROC( printf("push from memory, from [ Argument ]\n"); )

        ram_addr = (uint64_t)(*(ProcElem*)(proc->code + proc->IP));

        arg = *(ProcElem*)(proc->memory.ram + ram_addr);

        proc->IP += sizeof( ProcElem);
    }
    else if( mode & REGISTER_MASK )
    {
        arg = (ProcElem)( proc->regs[ *(proc->code + proc->IP) - kAX ] );

        ON_DEBUG_PROC( printf("push from register %d\n", *(proc->code + proc->IP) - kAX ); )

        proc->IP += 1;
    }
    else if( mode & INPUT_MASK)
    {
        ON_DEBUG_PROC( printf("standart push\n"); )

        arg = *(ProcElem*)(proc->code + proc->IP );
        proc->IP += sizeof( ProcElem );
    }
    else 
    {
        printf(RED "Something wrong in the instruction of Push\n" DELETE_COLOR);
    }
 
    // printf(RED "before: IP: %lu\n" DELETE_COLOR, proc->IP);
    // 
    // printf(RED "after: IP: %lu\n" DELETE_COLOR, proc->IP);

    return arg;
}


//===================INPUT FUNCTIONS========================

int DoPop( ProcElem arg, struct SPU* proc )
{
    char command = *(char*)(proc->code + proc->IP);
    char mode = ( ( command & ~(255 >> 3) ) );
    proc->IP += 1;

    ON_DEBUG_PROC
    (
        printf(GREEN "Subtype of command, first 3 bits\n" DELETE_COLOR);
        BinaryCharOutput( mode );
    )

    uint64_t ram_addr = 0;
    uint8_t reg_number = 0;

    if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) && (mode & INPUT_MASK) )
    {
        reg_number = *(char*)(proc->code + proc->IP) - kAX;
        ram_addr += (uint64_t)proc->regs[reg_number];

        ON_DEBUG_PROC( uint64_t first_arg = ram_addr; )

        proc->IP += 1;

        ram_addr += (uint64_t)( *(ProcElem*)(proc->code + proc->IP) );
        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;

        ON_DEBUG_PROC( uint64_t second_arg = ram_addr - first_arg; )

        proc->IP += sizeof( ProcElem);

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, to [ %lu + %lu ] \n" DELETE_COLOR, first_arg, second_arg ); )

        return 0;
    }
    else if ( (mode & MEMORY_MASK ) && (mode & REGISTER_MASK) )
    {
 
        reg_number = *(char*)(proc->code + proc->IP) - kAX;
        ram_addr += (uint64_t)proc->regs[reg_number];

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, address from register %d, which contains %lu\n" DELETE_COLOR, reg_number, ram_addr); )

        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;

        proc->IP += 1;

        return 0;
    }
    else if( (mode & MEMORY_MASK ) && (mode & INPUT_MASK) )
    {

        ram_addr += (uint64_t)( *(ProcElem*)(proc->code + proc->IP) );
        proc->IP += sizeof( ProcElem);

        ON_DEBUG_PROC( printf(ORANGE "pop to memory, addres from value:= %lu\n" DELETE_COLOR, ram_addr); )

        *(ProcElem*)(proc->memory.ram + ram_addr) = arg;

        return 0;
    }
    else if( mode & REGISTER_MASK )
    {

        reg_number = *(char*)(proc->code + proc->IP) - kAX;

        printf("reg number: %d", reg_number);

        ON_DEBUG_PROC( printf(ORANGE "pop to register %d\n" DELETE_COLOR, reg_number); )

        proc->regs[reg_number] = arg;

        printf("reg contains: %lf", proc->regs[reg_number]);

        proc->IP += 1;

        return 0;
    }
    else 
    {
        printf(RED "Something wrong in the instruction of Push\n" DELETE_COLOR);
        return -1;
    }
 
    // printf(RED "before: IP: %lu\n" DELETE_COLOR, proc->IP);
    // 
    // printf(RED "after: IP: %lu\n" DELETE_COLOR, proc->IP);

    return -1; 
}


int DoJump( struct SPU* proc)
{
    uint64_t jump = 0;

    if ( *( proc->code + proc->IP) == kJmp)  
    {
        proc->IP++;
        jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
        proc->IP = jump;
        return 0;
    }
    else if( proc->stack.size > 1)
    {
        ProcElem a = STACK_POP_CALL( &proc->stack);
        ProcElem b = STACK_POP_CALL( &proc->stack);

        STACK_PUSH_CALL( &proc->stack, b);
        STACK_PUSH_CALL( &proc->stack, a);

        switch( *(proc->code + proc->IP++ ) ) 
        {
            case kJa:
            {   
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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
                jump = (int64_t)( *(ProcElem*)( proc->code + proc->IP ) );
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

            default:
            {
                break;
            }
        }
    }
    else 
    {
        printf(RED "Not enough elements to comapare, and jump\n" DELETE_COLOR);
        return -1;
    }

    return -1; //HUUUUUUUUUUUUUUUUY
}
//=============================================================================================


//================================= MEMORY FUNCTIONS ==========================================

void RamDump( struct RAM* memory)
{
    printf(RED "Memory Demp\n" DELETE_COLOR);
    
    for(int i = 0; i < memory->capacity; i++)
    {
        printf("%8d", i);
    }
}

//=============================================================================================