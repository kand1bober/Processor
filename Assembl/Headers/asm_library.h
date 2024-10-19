#include <stdint.h>
#include <stdlib.h>

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER

const uint32_t SIGNATURE = 0x56564b;
const uint32_t VERSION = 2;

typedef int AssemblerElem;

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

    kJa = 13,
    kJae = 14,
    kJb = 15,
    kJbe = 16,
    kJe = 17,
    kJne = 18,
    kJmp = 19,

    kPushR = 20,
    kOutR = 21,
};

#endif
