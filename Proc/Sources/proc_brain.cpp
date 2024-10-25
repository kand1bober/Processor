#define DEBUG

#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"
#include "../Headers/proc_macros.h"
#include "../Headers/MyStackLib.h"

void Run(  struct SPU* proc_copy )
{   
    printf("Run processor:\n\n");

    struct SPU* proc = proc_copy;
    while(1)
    {
        char command = *(proc->code + proc->IP);

        char command_type = ( (command  & ~(255 << 5)) );

        printf("\n");
        ON_DEBUG_PROC
        (   
            printf(RED "Begin of cycle\n" DELETE_COLOR);
            printf("IP: %lu\n", proc->IP);
            printf(SINIY "Command, all 8 bits:\n" DELETE_COLOR);
            BinaryCharOutput( command );
            printf(PURPLE "Type of command, last 5 bits:\n" DELETE_COLOR); 
            BinaryCharOutput( command_type );
        )


        if ( proc->IP < proc->size_of_code)
        {

            switch( command_type )
            {   
                case kPush:
                {
                    PRINT_PROCESS( printf("Push\n"); )

                    proc->IP += 1;
                    ProcElem arg = GetArgPush( command, proc ); //Takes all arguments of this command, one or two

                    PRINT_PROCESS( printf("arg: %lf\n", arg); )

                    STACK_PUSH_CALL( &proc->stack, arg );

                    continue;
                }

                // case kPop:
                // {
                //     PRINT_PROCESS( printf("Pop\n"); )

                //     proc->IP += 1;
                //     ProcElem arg = 0;
                // }

                //=====JUMP PROCESSING=============
                case kJmpspace:
                {
                    printf(RED "JumpSpace skipped\n" DELETE_COLOR);
                    proc->IP += 1;
                    continue;
                }
                case kJa:
                {        
                    DoJump( command, proc );
                    continue;
                }
                case kJae:
                {
                    DoJump( command, proc );
                    continue;
                }
                case kJb:
                {
                    DoJump( command, proc );
                    continue;
                }
                case kJbe:
                {
                    DoJump( command, proc );
                    continue;
                }
                case kJe:
                {
                    DoJump( command, proc );
                    continue;
                }
                case kJne:
                {
                    DoJump( command, proc );
                    continue;
                }
                case kJmp:
                {
                    DoJump( command, proc );
                    continue;
                }

                case kCall:
                {
                    
                    continue;
                }
                //====END OF JUMP PROCESSING=========

                case kOut:
                {
                    PRINT_PROCESS( printf("Out\n"); )
                    ProcElem arg = 0;
                    proc->IP += 1;
                    arg = STACK_POP_CALL(&proc->stack);
                    printf("%lf\n", arg);
                    PAUSE;
                    continue;
                }

                case kIn:
                {
                    PRINT_PROCESS( printf("In\n"); )
                    ProcElem arg = 0;
                    scanf("%lf", &arg);
                    STACK_PUSH_CALL(&proc->stack, arg);
                    PAUSE;
                    continue;
                }

                case kAdd:
                {
                    PRINT_PROCESS( printf("Add\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, a + b);
                    PAUSE;
                    continue;
                }

                case kSub:
                {
                    PRINT_PROCESS( printf("Sub\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, (b - a) );

                    PAUSE;
                    continue;
                }

                case kMul:
                {
                    PRINT_PROCESS( printf("Mul\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, (a * b) );

                    PAUSE;
                    continue;
                }

                case kDiv:
                {
                    PRINT_PROCESS( printf("Div\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                    ProcElem b = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, (b / a) );

                    PAUSE;
                    continue;
                }

                case kSin:
                {
                    PRINT_PROCESS( printf("Sin\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);
                
                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, sin( (double)a ) );

                    continue;
                }

                case kCos:
                {
                    PRINT_PROCESS( printf("Cos\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, cos( (double)a ) );
                    
                    PAUSE;
                    continue;
                }

                case kRoot:
                {
                    PRINT_PROCESS( printf("Root\n"); )
                    ProcElem a = STACK_POP_CALL(&proc->stack);

                    proc->IP += 1;
                    STACK_PUSH_CALL(&proc->stack, sqrt( (double)a ) );

                    PAUSE;
                    continue;
                }

                case kDump:
                {
                    PRINT_PROCESS( printf("Dump\n"); )
                    #ifdef DEBUG_STACK_FUNCS
                        StackDump( &proc->stack, __FILE__, __PRETTY_FUNCTION__, __LINE__);
                    #endif

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }

                case kHlt:
                {
                    PRINT_PROCESS( printf("Hlt\n"); )
                    STACK_DTOR_CALL(&proc->stack);
                    printf("Processor stopped\n");
                    PAUSE;
                    break;
                }



                case kNull:
                {
                    printf("huuuuuy\n");

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }
                
                default:
                {
                    printf("SNTXERR: %d\n", command);

                    proc->IP += 1;
                    PAUSE;
                    continue;
                }
            }
            break;
        }
        else 
        {
            printf("Reached the end of programm with no halt, stoping\n");
            break;
        }
    }

}
