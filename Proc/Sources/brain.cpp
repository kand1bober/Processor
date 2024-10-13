#include "../Headers/library.h"
#include "../Headers/functions.h"
#include "../Headers/macros.h"

void Run(int* command_line, size_t size)
{
    struct SPU flow = {};
    
    STACK_CTOR_CALL(&flow.stack, START_CAPACITY);

    flow.IP = 0;
    while(1)
    {
        // int16_t command = 0;
        // scanf("%d", &command);

        int command = *(command_line + flow.IP);

        switch(command)
        {
            case kPush:
            {
                printf("push\n");
                ProcElem arg = 0;
                // scanf("%d", &arg);
                
                flow.IP += 1;
                arg = *(command_line + flow.IP);
                flow.IP += 1;

                STACK_PUSH_CALL(&flow.stack, arg);
                PAUSE;
                continue;
            }

            case kOut:
            {
                printf("push\n");
                ProcElem arg = 0;
                flow.IP += 1;
                arg = STACK_POP_CALL(&flow.stack);
                printf("%d\n", arg);
                PAUSE;
                continue;
            }
            case kAdd:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);
                ProcElem b = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, a + b);
                PAUSE;
                continue;
            }
            case kSub:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);
                ProcElem b = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, (b - a) );

                PAUSE;
                continue;
            }

            case kMul:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);
                ProcElem b = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, (a * b) );

                PAUSE;
                continue;
            }

            case kDiv:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);
                ProcElem b = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, (b / a) );

                PAUSE;
                continue;
            }

            case kSin:
            {
                //delete, when make on double
                ProcElem a = STACK_POP_CALL(&flow.stack);
            
                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, sin( (double)a ) );

                continue;
            }

            case kCos:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, cos( (double)a ) );
                
                PAUSE;
                continue;
            }

            case kRoot:
            {
                ProcElem a = STACK_POP_CALL(&flow.stack);

                flow.IP += 1;
                STACK_PUSH_CALL(&flow.stack, sqrt( (double)a ) );

                PAUSE;
                continue;
            }

            case kDump:
            {
                #ifdef DEBUG_STACK_FUNCS
                    StackDump(&flow.stack, __FILE__, __PRETTY_FUNCTION__, __LINE__);
                #endif

                flow.IP += 1;
                PAUSE;
                continue;
            }

            case kHlt:
            {
                STACK_DTOR_CALL(&flow.stack);
                printf("Processor stopped\n");
                PAUSE;
                break;
            }

            case kNull:
            {
                printf("huuuuuy\n");

                flow.IP += 1;
                PAUSE;
                continue;
            }
            
            default:
            {
                printf("SNTXERR: %d\n", command);

                flow.IP += 1;
                PAUSE;
                continue;
            }
        }
        break;

        // if ( strcmp(command, "in") == 0)
        // {
            
            
        // }

      
    }

}
