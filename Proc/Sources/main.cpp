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
        int command = 0;


        scanf("%d", &command);

        if ( command == push )
        {
            ProcElem arg = 0;
            scanf("%d", &arg);

            STACK_PUSH_CALL(&flow, arg);
            continue;
        }

        if ( command == out )
        {
            ProcElem arg = 0;
            arg = STACK_POP_CALL(&flow);

            printf("%d\n", arg);
            continue;
        }

        // if ( strcmp(command, "in") == 0)
        // {
            
            
        // }

        if ( command == add)
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, a + b);
            continue;
        }

        if ( command == sub)
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (b - a) );
            continue;
        }

        if ( command == mul )
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (a * b) );

            continue;
        }

        if ( command == divide )
        {
            ProcElem a = STACK_POP_CALL(&flow);
            ProcElem b = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, (b / a) );

            continue;
        }
        
        if ( command == sinus)
        {
            //delete, when make on double
            ProcElem a = STACK_POP_CALL(&flow);
        
            STACK_PUSH_CALL(&flow, sin( (double)a ) );

            continue;
        }
        
        if ( command == cosinus )
        {
            ProcElem a = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, cos( (double)a ) );
            
            continue;
        }
        
        if ( command == root )
        {
            ProcElem a = STACK_POP_CALL(&flow);

            STACK_PUSH_CALL(&flow, sqrt( (double)a ) );

            continue;
        }

        if ( command == dump )
        {
            StackDump(&flow, __FILE__, __PRETTY_FUNCTION__, __LINE__);

            continue;
        }

        if ( command == hlt )
        {
            STACK_DTOR_CALL(&flow);
            break;
        }

        if( command == 0)
        {
            printf("huuuuuy\n");
            continue;
        }

        else
            printf("SNTXERR: %d\n", command);

    }

}
