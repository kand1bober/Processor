
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../Headers/asm_library.h"

#ifndef ASM_FUNCTIONS_HEADER
#define ASM_FUNCTIONS_HEADER

void OutputFile(struct File_asm* file_a, struct File_code* file_b);
void InputFileStruct(struct File_asm* file);
void OutputFile(struct File_asm* file_a, struct File_code* file_b);
void CreateLinePointers(struct File_asm* file);
void CountManAndArg(struct File_asm* file);

struct Line_ptr
{
    char* start;    
    int length;
};

struct File_asm
{
    char name[30];
    int size_of_file;
    char* buffer;
    int lines_amount;
    int size_of_code;
    Line_ptr* lines_arr; //array of structures
    char* bitwise_buffer;
};


struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};


struct File_code
{
    Header head;
    char name[30];
    AssemblerElem* buffer;
};

#endif
