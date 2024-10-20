#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"

void BinaryOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf("%X", (unsigned)((number & (1 << i)) >> i) );
    }
}
