#define PRINT_DEBUG


#include <string.h>

#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"
#include "../Headers/asm_decoration.h"
#include "../Headers/asm_macros.h"



//=====CONVERT TO CODE AND WRITE IN OUTPUT======

// TODO: input.cpp
void OutputBuffer(struct File_asm* file_a, struct Output_buffer* output)
{
    struct Label_table spisok = {};
    LabelTableCtor(&spisok);

    FindLabels(&spisok, file_a);

    
    output->buffer = (char*)calloc(file_a->size_of_file, sizeof(char) );  //хуета, добавить realloc по ip, sizeof(char)
    output->ip = 0;
    char command_name[20] = {};

    //==================FIRST PROCESSING==========================
    for (int i = 0; i < file_a->lines_amount; i++)
    {
        sscanf( file_a->lines_arr[i].start, "%s", command_name );
        printf("\n");
        printf("iteration %d:   %s\n", i, command_name );
        //====Fill char array with comands and argumants===
        GetArg( command_name, &file_a->lines_arr[i], output, &spisok);
        //==================================================
        printf("\n");
    }
    printf("ip: %d\n", output->ip); //Check
    // ===================END OF FIRST=============================


    //===============SECOND PROCESSING=============================
    printf("size: %d\n", spisok.jump_count);
    int value = 0;
    char* target = nullptr;
    for(int i = 0; i < spisok.jump_count; i++)
    {
        value = spisok.labels[i].label_ip;
        target = output->buffer + spisok.jump_ip[i]; 
        memcpy(target, &value, sizeof(int) );  //TODO: зависит ли от типа ?
    }
    //=================END OF SECOND===============================

    LabelDump(&spisok);

    LabelTableDtor(&spisok);
}


void GetArg(char* command_name, struct Line_ptr* line, struct Output_buffer* output, struct Label_table* spisok)
{
    struct Cmd_strings CmdArray[] = 
    {
        {"null", kNull},
        {"push", kPush},
        {"pop", kPop},
        {"out", kOut},
        {"add", kAdd},
        {"in", kIn},
        {"sub", kSub},
        {"mul", kMul},
        {"div", kDiv},
        {"root", kRoot},
        {"sin", kSin},
        {"cos", kCos},
        {"dump", kDump},
        {"hlt", kHlt},

        {"AX", kAX},
        {"BX", kBX},
        {"CX", kCX},
        {"IP", kIP},
        
        {"ja", kJa},
        {"jae", kJae},
        {"jb", kJb},
        {"jbe", kJbe},
        {"je", kJe},
        {"jne", kJne},
        {"jmp", kJmp},
        {"jmpspace", kJmpspace},
    };
    
    int size = sizeof( CmdArray ) / sizeof( CmdArray[0] );

    int status = GetName( command_name, output, spisok, CmdArray, size );

    if( status == 0)
    {   
        char command_code = *(char*)(output->buffer + output->ip - 1 );

        if ( command_code == kPush)
        {
            GetArgPush(output, line);
        }
        else if ( command_code == kPop )
        {
            GetArgPop(output, line);
        }
        else if(( command_code == kJa ) || ( command_code == kJae ) || 
                ( command_code == kJb ) || ( command_code == kJbe ) || 
                ( command_code == kJe ) || ( command_code == kJne ) || 
                ( command_code == kJmp)) 
        {
            GetArgJump(MODE_1, output, line, spisok);
        }
        else 
        {
            // printf("zero argumants\n");
        }
    }
    else
    {
        // printf("wrong command\n");
    }
}


int GetName( char* command_name, struct Output_buffer* output, struct Label_table* spisok, struct Cmd_strings* array, int size)
{
    int status = 1;
    Label* search = {};

    // printf(RED "length of command_name: %ld\n" DELETE_COLOR, strlen(command_name) );

    for(int i = 0; (i < size); i++ )
    {
        if ( strcmp ( array[i].name , command_name ) == 0 )
        {
            *(char*)( output->buffer + output->ip ) = array[i].number;
            printf("enum code: %d\n", *(char*)(output->buffer + output->ip) );
            output->ip += 1;
            // printf("command from input: %s command from array: %s number from enum: %d\n", command_name, array[i].name, array[i].number);
            status = 0;
        }
    }

    if ( (status != 0) && ( search = SearchLabel(spisok, command_name, strlen(command_name) + 1) ) )
    {
        printf("Getname: only label\n");
        search->label_ip = output->ip;
        printf("found label: %d\n", search->label_ip);
        status = 2;
        *(char*)( output->buffer + output->ip ) = kJmpspace;
        printf("enum code: %d\n", *(char*)(output->buffer + output->ip) );
        output->ip += 1;

        // printf("wrong command\n");
        return status;
    }

    if ( status == 0 )
    {
        return status;
    }
    else 
    {
        return 1;
    }
}


int GetArgPush(struct Output_buffer* output, struct Line_ptr* line)
{
    AssemblerElem arg = 0;

    char* buffer = line->start + strlen("Push") + 1;
    

    if ( ( buffer = strchr( buffer, '[' ) ) != nullptr)
    {
        *(output->buffer + output->ip - 1) |= MEMORY_MASK;

        if ( strchr( buffer, ']' ) != nullptr )
            ;
        else
            printf(RED "Warning: No closing bracket :(\n" DELETE_COLOR);

        // printf("pos1: %p, ch: %c\n", buffer, *buffer);
        // printf("pos2:  %p, ch: %c\n", buffer, *buffer);
        // printf("string: %s\n", buffer);

        buffer += 2;

        if ( strncmp( buffer, "AX", 2 ) == 0 )  //TODO: убрать копипаст ввода, вынести часть ввода в функцию и зать не только в GetArgPush и GetArgPop ни о в GetJumpArg
        {
            // printf(RED "Memory with regs:\n" DELETE_COLOR);
            // printf(RED "reg AX:\n" DELETE_COLOR);

            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); )

            *( output->buffer + (output->ip++) ) = kAX;
            return 0;
        }
        else if ( strncmp( buffer, "BX", 2 ) == 0 )
        {
            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); )

            *( output->buffer + (output->ip++) ) = kBX;
            return 0;
        }
        else if( strncmp( buffer, "CX", 2 ) == 0 )
        {
            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); ) 

            *( output->buffer + (output->ip++) ) = kCX;
            return 0;
        }
        else 
        {
            // printf(RED "onlu mamory:\n" DELETE_COLOR);
            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); ) 

            return 0;
        }
    }
    else
    {
        buffer = line->start + strlen("Push") + 1;

        // printf("No []: \n");
        // printf("pos:  %d\n", output->ip);
        // printf("%s\n", output->buffer + output->ip);
        // printf(RED "only regs :\n" DELETE_COLOR);

        if ( strncmp( buffer, "AX", 2 ) == 0 )
        {
            // printf(RED "reg AX:" DELETE_COLOR);

            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); )

            *( output->buffer + (output->ip++) ) = kAX;
            return 0;
        }
        else if ( strncmp( buffer, "BX", 2 ) == 0 )
        {
            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); )

            *( output->buffer + (output->ip++) ) = kBX;
            return 0;
        }
        else if( strncmp( buffer, "CX", 2 ) == 0 )
        {
            *( output->buffer + output->ip - 1 ) |= REGISTER_MASK;

            ON_DEBUG( BinaryCharOutput(*(output->buffer + output->ip - 1 ) ); )

            *( output->buffer + (output->ip++) ) = kCX;
            return 0;
        }
        else 
        {

            buffer = line->start + strlen("Push");
            *(output->buffer + output->ip - 1) |= INPUT_MASK;

            // printf("simple input\n");
            // printf("pos:  %d\n", output->ip);
            if ( sscanf( buffer, "%d", &arg ) == 1 )
            {
                printf("arg: %d\n", arg);
                *(int*)( output->buffer + output->ip ) = arg;

                ON_DEBUG
                (
                    BinaryCharOutput( *( output->buffer + output->ip - 1 ) );
                    printf(" ");
                    BinaryIntOutput( *(int*)( output->buffer + output->ip ) );
                )

                output->ip += sizeof( AssemblerElem );
            }
            else 
            {
                return -1;
            }
        }
    } 
    return -2; // kakoyto pizdec
}


int GetArgPop(struct Output_buffer* output, struct Line_ptr* line)
{
    int arg = 0;

    if ( sscanf( line->start + strlen("Pop"), "%d", &arg) == 1 )
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

    file->head.size_of_code = file->output_buffer.ip;
    file->head.sign = SIGNATURE;
    file->head.ver = VERSION;

    fwrite(&file->head, 1, sizeof(file->head), output_stream);
    fwrite(file->output_buffer.buffer, file->output_buffer.ip, sizeof(char), output_stream);
    fclose(output_stream);
    //==============================================
}


void BinaryCharOutput(char number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR , (unsigned)((number & (1 << i)) >> i) );
    }
}


void BinaryIntOutput(int number)
{
    int l = 8 *  sizeof(number);
    for (int i = l - 1; i >= 0; i--)
    {
        printf(YELLOW "%X" DELETE_COLOR, (unsigned)((number & (1 << i)) >> i) );
    }
}