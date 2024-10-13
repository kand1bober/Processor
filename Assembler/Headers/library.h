#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER


struct File_code
{
    const char* name;
    const char* author;
    int size_code;
};


struct File_asm
{
    const char* name;
    int size;
    char* buffer;
};


enum commands
{
    kNull = 0,
    kPush = 1,
    kOut = 2,
    kAdd = 3,
    kIn = 4,
    kSub = 5,
    kMul = 6,
    kDiv = 7,
    kRoot = 8,
    kSin = 9,
    kCos = 10,
    kDump = 11,
    kHlt = 12,
};

#endif
