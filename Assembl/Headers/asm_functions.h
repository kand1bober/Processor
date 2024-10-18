
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

struct File_asm
{
    char name[30];
    int size_of_file;
    char* buffer;
    int size_of_code;
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
