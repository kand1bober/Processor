#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "proc_library.h"

#include "MyStackLib.h"

#ifndef PROC_FUNCTIONS_HEADER
#define PROC_FUNCTIONS_HEADER

struct File_proc 
{
    char name[30];
    char author[30];
    size_t size_of_code;
    ProcElem* buffer;
};

void Run(int* command_line, size_t size);
void InputFileCode(struct File_proc* file);

#endif