#ifndef PROJECT_PROC_ENUM_HEADER
#define PROJECT_PROC_ENUM_HEADER

enum Commands
{
    kNull = 0,
    kAX = 1,
    kBX = 2,
    kCX = 3,
    kPush = 4,
    kPop = 5,
    kOut = 6,
    kAdd = 7,
    kIn = 8,
    kSub = 9,
    kMul = 10,
    kDiv = 11,
    kRoot = 12,
    kSin = 13,
    kCos = 14,
    kDump = 15,
    kHlt = 16,

    kJa = 17,
    kJae = 18,
    kJb = 19,
    kJbe = 20,
    kJe = 21,
    kJne = 22,
    kJmp = 23,
    kJmpspace = 24,

    kCall = 25,
    kRet = 26,
};



const unsigned char MEMORY_MASK = 128;
const unsigned char REGISTER_MASK = 64;
const unsigned char INPUT_MASK = 32;


#endif