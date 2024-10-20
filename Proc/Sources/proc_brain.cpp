#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"
#include "../Headers/proc_macros.h"

void Run(char* command_line, size_t size_of_code)
{   
    printf("Run processor:\n\n");

    struct SPU flow = {};
    
    STACK_CTOR_CALL(&flow.stack, START_CAPACITY);

    flow.IP = 0;
    while(1)
    {
        char command = *(command_line + flow.IP);
        if ( (size_t)flow.IP < size_of_code)
        {
            printf("IP: %d\n", flow.IP);

            switch(command)
            {
                // case kPush:
                // {
                //     // printf("Push\n");
                //     ProcElem arg = 0;
                    
                //     flow.IP += 1;
                //     arg = *(command_line + flow.IP);
                //     flow.IP += 1;

                //     STACK_PUSH_CALL(&flow.stack, arg);
                //     PAUSE;
                //     continue;
                // }

                // case kPushR:
                // {
                //     flow.IP++;
                //     if( *(command_line + flow.IP) == AX )
                //     {
                //         flow.AX = STACK_POP_CALL(&flow.stack);
                //         flow.IP++;
                //     }

                //     else if( *(command_line + flow.IP) == BX )
                //     {
                //         flow.BX = STACK_POP_CALL(&flow.stack);
                //         flow.IP++;
                //     }
                //     else if( *(command_line + flow.IP) == CX )
                //     {
                //         flow.CX = STACK_POP_CALL(&flow.stack);
                //         flow.IP++;
                //     }
                // }

                // case kPop:
                // {
                
                // }






                // case kJa:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b > a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;                                                            
                // }

                // case kJae:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b >= a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;                                                            
                // }

                // case kJb:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b < a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;                                                            
                // }

                // case kJbe:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b <= a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;                                                            
                // }

                // case kJe:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b == a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;                                                            
                // }

                // case kJne:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     if(b != a)
                //         flow.IP = jump;
                //     else
                //         flow.IP++;
                //     continue;    
                // }
                
                // case kJmp:
                // {
                //     uint32_t jump = 0;
                //     ProcElem a = STACK_POP_CALL(&flow.stack);
                //     ProcElem b = STACK_POP_CALL(&flow.stack);

                //     STACK_PUSH_CALL(&flow.stack, b);
                //     STACK_PUSH_CALL(&flow.stack, a);
                //     flow.IP++;
                //     jump = *(command_line + flow.IP);
                    
                //     flow.IP = jump;
                //     flow.IP++;

                //     continue;    
                // }









                case kOut:
                {
                    // printf("Out\n");
                    ProcElem arg = 0;
                    flow.IP += 1;
                    arg = STACK_POP_CALL(&flow.stack);
                    printf("%d\n", arg);
                    PAUSE;
                    continue;
                }

                case kIn:
                {
                    // printf("In\n");
                    ProcElem arg = 0;
                    scanf("%d", &arg);
                    STACK_PUSH_CALL(&flow.stack, arg);
                    PAUSE;
                    continue;
                }

                case kAdd:
                {
                    // printf("Add\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);
                    ProcElem b = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, a + b);
                    PAUSE;
                    continue;
                }

                case kSub:
                {
                    // printf("Sub\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);
                    ProcElem b = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, (b - a) );

                    PAUSE;
                    continue;
                }

                case kMul:
                {
                    // printf("Mul\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);
                    ProcElem b = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, (a * b) );

                    PAUSE;
                    continue;
                }

                case kDiv:
                {
                    // printf("Div\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);
                    ProcElem b = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, (b / a) );

                    PAUSE;
                    continue;
                }

                case kSin:
                {
                    // printf("Sin\n");
                    //delete, when make on double
                    ProcElem a = STACK_POP_CALL(&flow.stack);
                
                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, sin( (double)a ) );

                    continue;
                }

                case kCos:
                {
                    // printf("Cos\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, cos( (double)a ) );
                    
                    PAUSE;
                    continue;
                }

                case kRoot:
                {
                    // printf("Root\n");
                    ProcElem a = STACK_POP_CALL(&flow.stack);

                    flow.IP += 1;
                    STACK_PUSH_CALL(&flow.stack, sqrt( (double)a ) );

                    PAUSE;
                    continue;
                }

                case kDump:
                {
                    // printf("Dump\n");
                    #ifdef DEBUG_STACK_FUNCS
                        StackDump(&flow.stack, __FILE__, __PRETTY_FUNCTION__, __LINE__);
                    #endif

                    flow.IP += 1;
                    PAUSE;
                    continue;
                }

                case kHlt:
                {
                    printf("Hlt\n");
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
        }
        else 
        {
            printf("Reached the end of programm with no halt, stoping\n");
            break;
        }
        
    }

}
