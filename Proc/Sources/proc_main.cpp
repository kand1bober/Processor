#include "../Headers/proc_library.h"
#include "../Headers/proc_functions.h"

int main()
{
    struct File_proc file = {};

    InputFileCode(&file);

    Run(file.buffer, file.size_of_code);

    free(file.buffer);

    return 0;   
}

