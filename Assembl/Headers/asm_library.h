#include <stdint.h>
#include <stdlib.h>

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER

const uint32_t SIGNATURE = 0x56564b;
const uint32_t VERSION = 2;

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

    kJa = 14,
    kJae = 15,
    kJb = 16,
    kJbe = 17,
    kJe = 18,
    kJne = 19,
    kJmp = 20,

    kAX = 21,
    kBX = 22,
    kCX = 23,
    kIP = 24,
};

struct Cmd_strings
{
    char  name[10];
    enum Commands number;
};

#endif
