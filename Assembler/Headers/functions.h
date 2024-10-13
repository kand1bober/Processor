#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

void InputFileStruct(const char* name);
// void CharToIntAndStruct(struct File_asm* file);
void OutputFile(struct File_asm* a, struct File_asm* b);

#endif