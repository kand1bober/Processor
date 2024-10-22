#include <cmath>
#include <stdint.h>
#include <stdlib.h>

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER

const int LABEL_ARR_SIZE = 20;

const uint32_t SIGNATURE = 0x56564b;
const uint32_t VERSION = 3;

typedef int AssemblerElem;

enum Commands
{
    kNull = 0,
    kPush = 1,
    kPop = 2,
    kOut = 3,
    kAdd = 4,
    kIn = 5,
    kSub = 6,
    kMul = 7,
    kDiv = 8,
    kRoot = 9,
    kSin = 10,
    kCos = 11,
    kDump = 12,
    kHlt = 13,

    kAX = 14,
    kBX = 15,
    kCX = 16,
    kIP = 17,

    kJa = 18,
    kJae = 19,
    kJb = 20,
    kJbe = 21,
    kJe = 22,
    kJne = 23,
    kJmp = 24,
    kJmpspace = 25,
};

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
