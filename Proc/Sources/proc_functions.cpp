#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"

void BinaryCharOutput(char number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR , (unsigned)((number & (1 << i)) >> i) );
    }
}


void BinaryIntOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR, (unsigned)((number & (1 << i)) >> i) );
    }
}

int GetArgPush( char command, struct SPU* proc)
{
    ProcElem arg = 0;

    

    return 0;
}