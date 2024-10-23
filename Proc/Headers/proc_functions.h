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
    int size_of_code;

    int16_t AX;
    int16_t BX;
    int16_t CX;
    int16_t IP;
};


void Run( struct SPU* flow_copy );
void InputFileCode( struct File_proc* file );
void BinaryIntOutput( int number );
void BinaryCharOutput( char number );
int GetArgPush( char command, struct SPU* proc );
int GetArgPop( char command, struct SPU* proc );

#endif