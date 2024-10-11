#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../Headers/MyStackLib.h"

typedef int ProcElem;

void Run();

int main()
{
    Run();

    return 0;
}

void Run()
{
    Stack_t flow = {};

    STACK_CTOR_CALL(&flow, START_CAPACITY);

    while(1)
    {
        char command_line[10] = "Hello";

        scanf("%s", command_line);

        if ( strcmp(command_line, "push") == 0 )
        {
            ProcElem arg = 0;
            scanf("%d", &arg);

            STACK_PUSH_CALL(&flow, arg);
            continue;
        }

        if ( strcmp(command_line, "out") == 0 )
        {
            ProcElem arg = 0;
            arg = STACK_POP_CALL(&flow);

            printf("%d\n", arg);
            continue;
        }

        // if ( strcmp(command_line, "in") == 0)
        // {
            
            
        // }

        if ( strcmp(command_line, "add") == 0 )
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, a + b);
            continue;
        }

        if ( strcmp(command_line, "sub") == 0 )
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (b - a) );
            continue;
        }

        if ( strcmp(command_line, "mul") == 0)
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (a * b) );

            continue;
        }

        if ( strcmp(command_line, "div") == 0)
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (b / a) );

            continue;
        }
        
        if ( strcmp(command_line, "sin") == 0)
        {
            //delete, when make on double
            ProcElem a = STACK_POP_CALL(&flow);
        
            STACK_PUSH_CALL(&flow, sin( (double)a ) );

            continue;
        }
        
        if ( strcmp(command_line, "cos") == 0)
        {
            ProcElem a = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, cos( (double)a ) );
            
            continue;
        }
        
        if ( strcmp(command_line, "sqrt") == 0)
        {
            ProcElem a = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, sqrt( (double)a ) );

            continue;
        }

        if ( strcmp(command_line, "dump") == 0 )
        {
            StackDump(&flow, __FILE__, __PRETTY_FUNCTION__, __LINE__);

            continue;
        }

        if ( strcmp(command_line, "hlt") == 0 )
        {
            STACK_DTOR_CALL(&flow);
            break;
        }

        else
            printf("SNTXERR: %s\n", command_line);

    }

}
