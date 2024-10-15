#include <stdlib.h>

#include "../../Parser/Headers/pars_library.h"

#ifndef ASSEMBLER_LIBRARY_HEADER
#define ASSEMBLER_LIBRARY_HEADER

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
    KJmp = 19,

    kPushR = 20,
    kOutR = 21,
};

#endif