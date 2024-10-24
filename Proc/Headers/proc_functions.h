#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "proc_library.h"

#include "MyStackLib.h"


#ifndef PROC_FUNCTIONS_HEADER
#define PROC_FUNCTIONS_HEADER

struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};

struct File_proc 
{
    Header head;
    char name[30];
    char* buffer; 
};

struct Line_ptr
{
    char* begin;    
    int length;
};

struct SPU
{
    Stack_t stack;

    char* code;
    uint64_t size_of_code;

    double* regs;

    uint64_t IP;
};


void Run( struct SPU* flow_copy );
void InputFileCode( struct File_proc* file, struct SPU* proc );
void BinaryIntOutput( int number );
void BinaryCharOutput( unsigned char number );
ProcElem GetArgPush( char command, struct SPU* proc );
ProcElem GetArgPop( char command, struct SPU* proc );
void DoJump( char command, struct SPU* proc );

const unsigned char MEMORY_MASK = 128;
const unsigned char REGISTER_MASK = 64;
const unsigned char INPUT_MASK = 32;

#endif