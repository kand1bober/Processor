#include <stdint.h>

#include "MyStackLib.h"

#ifndef PROC_LIBRARY_HEADER
#define PROC_LIBRARY_HEADER

typedef int ProcElem;

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
    AX = 22,
    BX = 23,
    CX = 24,
};

struct SPU
{
    Stack_t stack;

    //registers, maybe, should make separete structure
    int16_t AX;
    int16_t BX;
    int16_t CX;
    int16_t IP;
};

#endif