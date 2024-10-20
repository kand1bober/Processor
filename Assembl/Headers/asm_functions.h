
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../Headers/asm_library.h"

#ifndef ASM_FUNCTIONS_HEADER
#define ASM_FUNCTIONS_HEADER

//==============INPUT=====================
void OutputFile(struct File_code* file);
void InputFileStruct(struct File_asm* file);
void OutputBuffer(struct File_asm* file_a, struct Output_buffer* output);
void CreateLinePointers(struct File_asm* file);
void CountManAndArg(struct File_asm* file);
//========================================

//============GET ARGUMENT FOR FUNCITONS WITH ARGUMENTS============
void GetArg(char* command_buffer, struct Line_ptr* line, struct Output_buffer* output);
int GetName( char* command_name, struct Output_buffer* output, struct Cmd_strings* array, int size);
int GetArgPush(struct Output_buffer* output, struct Line_ptr* line);
int GetArgPop(struct Output_buffer* output, struct Line_ptr* line);
//==================================================================

//=========LABLE TABLE==============================================
void LabelTableCtor(struct Label_table* spisok);
void LabelTableDtor(struct Label_table* spisok);
void FindLabels(struct Label_table* spisok, struct File_asm* file);
int WriteLabel(struct Label_table* spisok, char* ptr, size_t length);
char* SkipSpaces(char* ptr);
//==================================================================

//========ADDITIONAL===============
void BinaryIntOutput(int number);
void BinaryCharOutput(char number);
//=================================

struct Line_ptr
{
    char* start;    
    int length;
};

struct File_asm
{
    char name[30];
    int size_of_file;
    char* buffer;
    int lines_amount;
    int size_of_code;
    Line_ptr* lines_arr; //array of structures
};


struct Header
{
    uint32_t sign;
    uint32_t ver;
    uint32_t size_of_code;
    uint32_t reserved;
};

struct Output_buffer
{
    char* buffer;
    int ip;
};

struct File_code
{
    Header head;
    char name[30];
    Output_buffer output_buffer;
};


const unsigned char MEMORY_MASK = 128;
const unsigned char REGISTER_MASK = 64;
const unsigned char INPUT_MASK = 32;

#endif
