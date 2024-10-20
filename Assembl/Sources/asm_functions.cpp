#include <string.h>
#include <ctype.h>

#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"

//=====CONVERT TO CODE AND WRITE IN OUTPUT======

// TODO: input.cpp
void OutputBuffer(struct File_asm* file_a, struct Output_buffer* output)
{
    output->buffer = (char*)calloc(file_a->size_of_file, sizeof(char) );  //хуета
    output->ip = 0;

    char command_buffer_1[20] = {};
    char command_name[20] = {};

    for (int i = 0; i < file_a->lines_amount; i++)
    {
        sscanf( file_a->lines_arr[i].start, "%s", command_buffer_1 );
        sprintf( command_name, "k%c%s", toupper( command_buffer_1[0] ), command_buffer_1 + 1);
        printf("iteration %d:   %s\n", i, command_name );

        //====Fill char array with coomands and argumants===
        GetArg( command_name, &file_a->lines_arr[i], output );
        //==================================================
        printf("\n");
    }
    printf("\n");

    //============Check===============
    // for(int i = 0; i < file_a->size_of_file; i++)
    // {
    //     printf("%d ", *(char*)(output->buffer + i) );
    // }

    printf("\nip: %d\n", output->ip);
    //===============================
}


void GetArg(char* command_name, struct Line_ptr* line, struct Output_buffer* output)
{
    struct Cmd_strings CmdArray[] = 
    {
        {"kNull", kNull},
        {"kPush", kPush},
        {"kPop", kPop},
        {"kOut", kOut},
        {"kAdd", kAdd},
        {"kIn", kIn},
        {"kSub", kSub},
        {"kMul", kMul},
        {"kDiv", kDiv},
        {"kRoot", kRoot},
        {"kSin", kSin},
        {"kCos", kCos},
        {"kDump", kDump},
        {"kHlt", kHlt},
        {"kJa", kJa},
        {"kJae", kJae},
        {"kJb", kJb},
        {"kJbe", kJbe},
        {"kJe", kJe},
        {"kJne", kJne},
        {"kJmp", kJmp},
        {"kAX", kAX},
        {"kBX", kBX},
        {"kCX", kCX},
        {"kIP", kIP},
    };
    int size = sizeof( CmdArray ) / sizeof( CmdArray[0] );

    int status = GetName( command_name, output, CmdArray, size );

    if( status == 0)
    {   
        if ( *(char*)(output->buffer + output->ip - 1) == kPush)
        {
            GetArgPush(output, line);
        }
        else if ( *(char*)(output->buffer + output->ip - 1 ) == kPop )
        {
            GetArgPop(output, line);
        }
        // TODO: add Jumps and two-stage processing 
        // else if ( *(int*)(output->buffer + output->ip) == kJa) 
        // {

        // }
        else 
        {
            printf("zero argumants\n");
        }
    }
    else
    {
        printf("wrong command\n");
    }
}


int GetName( char* command_name, struct Output_buffer* output, struct Cmd_strings* array, int size)
{
    int status = -1;

    for(int i = 0; i < size; i++ )
    {
        if ( strcmp ( array[i].name , command_name ) == 0 )
        {
            *(char*)(output->buffer + output->ip) = array[i].number;
            printf("enum code: %d\n", *(char*)(output->buffer + output->ip) );
            output->ip += 1;

            // printf("command from input: %s command from array: %s number from enum: %d\n", command_name, array[i].name, array[i].number);
            status = 0;
        }
    }

    if ( status == 0)
    {
        return 0;
    }
    else 
    {
        printf("wrong command\n");
        return -1;
    }
}


int GetArgPush(struct Output_buffer* output, struct Line_ptr* line)
{
    int arg = 0;
    int status = sscanf( line->start + strlen("kPush"), "%d", &arg);
    if ( status )
    {
        printf("arg: %d\n", arg);

        *(int*)(output->buffer + output->ip) = arg;
        output->ip += sizeof(AssemblerElem);

        return 0;
    }
    else
    {
        // printf("arg: huy\n");
        return 1;
    }
}


int GetArgPop(struct Output_buffer* output, struct Line_ptr* line)
{
    int arg = 0;

    if ( sscanf( line->start + strlen("kPop"), "%d", &arg) == 1 )
    {
        printf("arg: %d\n", arg);   

        *(int*)(output->buffer + output->ip) = arg;
        output->ip += sizeof(AssemblerElem);

        return 0;
    }
    else
    {
        // printf("arg: huy\n");
        return 1;
    }
}


void OutputFile(struct File_code* file)
{   
    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    FILE* output_stream = fopen(filepath, "wb");

    file->head.size_of_code = file->output_buffer.ip ;
    file->head.sign = SIGNATURE;
    file->head.ver = VERSION;

    fwrite(&file->head, 1, sizeof(file->head), output_stream);
    fwrite(file->output_buffer.buffer, file->output_buffer.ip, sizeof(char), output_stream);
    fclose(output_stream);
    //==============================================
}