#include <cmath>
#include <stdint.h>
#include <stdlib.h>

#include "../../proc_project/enum.h"

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER

const int LABEL_ARR_SIZE = 20;

const uint32_t SIGNATURE = 0x56564b;
const uint32_t VERSION = 3;

typedef double AssemblerElem;

struct Cmd_strings
{
    char name[10];
    enum Commands number;
};

struct Label 
{
    char name[10];
    int label_ip;
    int jump_ip;
};

struct Label_table
{
    Label* labels;
    int amount;
    int jump_count;
};

#endif
