#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "proc_library.h"

// #include "MyStackLib.h"

#ifndef PROC_FUNCTIONS_HEADER
#define PROC_FUNCTIONS_HEADER

struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};

struct File_proc 
{
    Header head;
    char name[30];
    ProcElem* buffer; 
};

struct Line_ptr
{
    char* begin;    
    int length;
};

void Run(int* command_line, size_t size);
void InputFileCode(struct File_proc* file);

#endif