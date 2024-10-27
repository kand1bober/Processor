#define PRINT_DEBUG


#include <string.h>

#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"
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

        ON_DEBUG
        (
            printf("\n");
            printf(BLUE "ip before iteration: %d\n" DELETE_COLOR, output->ip); 
            printf("iteration %d:   %s\n", i, command_name );
        )

        //====Fill char array with comands and argumants===
        GetArg( command_name, &file_a->lines_arr[i], output, &spisok);
        //==================================================

        ON_DEBUG( printf(ORANGE "\nip after iteration: %d\n" DELETE_COLOR, output->ip); )
    }
    // ===================END OF FIRST=============================


    //===============SECOND PROCESSING=============================
    AssemblerElem value = 0;
    char* target = nullptr;
    for(int i = 0; i < spisok.jump_count; i++)
    {
        value = spisok.labels[i].label_ip;
        target = output->buffer + spisok.labels[i].jump_ip; 
        memcpy(target, &value, sizeof(AssemblerElem) );  //TODO: зависит ли от типа ?
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
        
        {"ja", kJa},
        {"jae", kJae},
        {"jb", kJb},
        {"jbe", kJbe},
        {"je", kJe},
        {"jne", kJne},
        {"jmp", kJmp},
        {"jmpspace", kJmpspace},

        {"call", kCall},
        {"ret", kRet},
    };
    
    int size = sizeof( CmdArray ) / sizeof( CmdArray[0] );

    int status = GetName( command_name, output, spisok, CmdArray, size );

    if( status == 0)
    {   
        char command_code = *(char*)(output->buffer + output->ip - 1 );

        if ( command_code == kPush)
        {
            BinaryCharOutput( *(char*)(output->buffer + output->ip - 1) );
            ON_DEBUG
            ( 
                printf("\n");
                GetArgPush(output, line);
                printf("\n");
            )
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
            GetArgJump(output, line, spisok);
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

            ON_DEBUG( printf("enum code: %d\n", *(char*)(output->buffer + output->ip) ); )

            output->ip += 1;
            // printf("command from input: %s command from array: %s number from enum: %d\n", command_name, array[i].name, array[i].number);
            status = 0;
        }
    }
    //TODO: сделать поиск по двум массивам. Регистров и комманд

    if ( (status != 0) && ( search = SearchLabel(spisok, command_name, strlen(command_name) + 1) ) )
    {
        // printf("Getname: only label\n");
        search->label_ip = output->ip;
        // printf("found label: %d\n", search->label_ip);
        status = 2;
        *(char*)( output->buffer + output->ip ) = kJmpspace;

        ON_DEBUG( printf("enum code: %d\n", *(char*)(output->buffer + output->ip) ); ) 

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


int GetArgPush( struct Output_buffer* output, struct Line_ptr* input)
{
    ON_DEBUG( char* instruction = (char*)(output->buffer + output->ip - 1); )

    input->start = SkipSpaces( input->start );
    input->start += strlen("push");
    input->start = SkipSpaces( input->start );

    if ( strchr( input->start, '[' ) != nullptr )
    {
        printf("Push to memory\n");
        //===============================================================
        if ( strchr( input->start, ']' ) != nullptr )
        {
            ;
        }   
        else 
        {
            printf(RED "WARNING: no closing bracket ']' \n" DELETE_COLOR);
        }
        //================================================================

        *(output->buffer + output->ip - 1) |= MEMORY_MASK;

        input->start += 1;

        int kolvo_arg = GetArgNum( input );

        if( kolvo_arg == 2 ) 
        {
            GetRegister( output, input, instruction );
            output->ip += 1;

            SkipOp( input );

            GetValue( output, input, instruction );
            output->ip += sizeof(AssemblerElem);
        }
        else if ( kolvo_arg == 3 )
        {
            GetRegister( output, input, instruction );
            output->ip += 1;
        }
        else if ( kolvo_arg == 4)
        {
            GetValue( output, input, instruction );
            output->ip += sizeof(AssemblerElem);
        }

        ON_DEBUG
        (
            printf("\n");
            BinaryCharOutput( *instruction );
            printf("\n");
        )
    }
    else 
    {
        int kolvo_arg = GetArgNum( input );

        // printf(RED "kod argumenta without[ ]: %d" DELETE_COLOR, kolvo_arg);

        if( kolvo_arg == 2 ) 
        {
            printf(RED "warning: too many arguments for push" DELETE_COLOR);
        }
        else if ( kolvo_arg == 3 )
        {
            GetRegister( output, input, instruction );
            output->ip += 1;
        }
        else if ( kolvo_arg == 4)
        {
            GetValue( output, input, instruction );
            output->ip += sizeof(AssemblerElem);
        }

        ON_DEBUG
        (
            printf("\n");
            BinaryCharOutput( *instruction );
            printf("\n");
        )
    }
    
    return 0;
}


int GetArgNum( struct Line_ptr* input )
{
    input->start = SkipSpaces( input->start );
    printf(RED "string in GetArgNum:\n%s\n" DELETE_COLOR , input->start);

    char trash[2] = {};
    AssemblerElem value = 0;

    if ( strchr(input->start, '+' ) != nullptr )               
    {
        ON_DEBUG( printf(SINIY "Two arguments\n" DELETE_COLOR); )
        return 2;
    }
    else if( sscanf(input->start, "%lf", &value) == 1 )  
    {
        ON_DEBUG( printf(SINIY "Only value argument\n" DELETE_COLOR); )
        return 4;
    }
    else if ( sscanf(input->start, "%2c", trash) == 1)
    {
        if ( (strcmp( trash, "AX") == 0 ) || ( strcmp( trash, "BX") == 0 ) || ( strcmp( trash, "CX") == 0 ) )
        {
            ON_DEBUG( printf(SINIY "Only register argument\n" DELETE_COLOR); )
            return 3;
        }
        else 
        {
            printf("wrong register\n");
        }
    }
    

    return -1;
}


void SkipOp( struct Line_ptr* input )
{
    char* operation = 0;

    input->start = SkipSpaces( input->start );

    // printf("\nin SkipOp: %s\n", in_buf);

    if ( ( operation = strchr(input->start, '+') ) != nullptr)   
    {
        input->start = operation + 1;
        input->start = SkipSpaces( input->start );
    }
    else
    {
        printf(RED "warning: no operand between values\n" DELETE_COLOR);
    }
}


int GetRegister( struct Output_buffer* output, struct Line_ptr* input, char* instruction ) 
{
    char reg = 0;

    input->start = SkipSpaces( input->start );

    char first_letter = 0, second_letter = 0;

    // printf("\nin GetRegister: %s\n", in_buf);

    if ( sscanf(input->start, "%c", &first_letter ) == 1 )
    {
        if ( (first_letter == 'A') || (first_letter == 'B') || (first_letter == 'C') )
        {
            input->start += 1;

            if ( sscanf(input->start, "%c", &second_letter ) == 1 )
            {
                input->start += 1;
            }
            else 
            {
                ON_DEBUG( printf(RED "wrong syntax of second letter\n" DELETE_COLOR); )
                return -1;
            }
        }
    }
    else 
    {
        ON_DEBUG( printf(RED "wrong syntax of first letter\n" DELETE_COLOR); )
        return -1;
    }

    *instruction |= REGISTER_MASK;

    switch (first_letter)
    {
        case 'A':
        {
            *(char*)( output->buffer + output->ip ) = kAX; 
            break;
        }
        case 'B':
        {
            *(char*)( output->buffer + output->ip ) = kBX;
            break;
        }
        case 'C':
        {
            *(char*)( output->buffer + output->ip ) = kCX;
            break;
        }
    }
    return reg;
}


int GetValue( struct Output_buffer* output, struct Line_ptr* input, char* instruction )
{
    AssemblerElem arg = 0;

    input->start = SkipSpaces( input->start );
    if ( sscanf(input->start, "%lf", &arg) == 1 )
    {
        *(AssemblerElem*)(output->buffer + output->ip ) = arg;
        printf(ORANGE "value argument: %lf\n" DELETE_COLOR, arg);

        *instruction |= INPUT_MASK; //TODO:

        printf("\n");
        // BinaryCharOutput( *(char*)(output->buffer + output->ip - 1) );
        printf("\n");
    }
    else 
    {
        printf(RED "wrong value argument\n" DELETE_COLOR);
    }

    return arg; 
}

//================================================================================



int GetArgPop( struct Output_buffer* output, struct Line_ptr* input ) 
{
    ON_DEBUG( char* instruction = (output->buffer + output->ip - 1); )

    input->start = SkipSpaces( input->start );
    input->start += strlen("pop");
    input->start = SkipSpaces( input->start );

    if ( strchr( input->start, '[' ) != nullptr )
    {
        printf("Pop from memory\n");
        //===============================================================
        if ( strchr( input->start, ']' ) != nullptr )
        {
            ;
        }   
        else 
        {
            printf(RED "WARNING: no closing bracket ']' \n" DELETE_COLOR);
        }
        //================================================================

        *(output->buffer + output->ip - 1) |= MEMORY_MASK;

        input->start += 1;

        int kolvo_arg = GetArgNum( input );

        if( kolvo_arg == 2 ) 
        {
            GetRegister( output, input, instruction );
            output->ip += 1;

            SkipOp( input );

            GetValue( output, input, instruction );
            output->ip += sizeof(AssemblerElem);
        }
        else if ( kolvo_arg == 3 )
        {
            GetRegister( output, input, instruction );
            output->ip += 1;
        }
        else if ( kolvo_arg == 4)
        {
            GetValue( output, input, instruction );
            output->ip += sizeof(AssemblerElem);
        }

        ON_DEBUG
        (
            printf("\n");
            BinaryCharOutput( *instruction );
            printf("\n");
        )
    }
    else 
    {
        int kolvo_arg = GetArgNum( input );

        // printf(RED "kod argumenta without[ ]: %d" DELETE_COLOR, kolvo_arg);

        if( kolvo_arg == 2 ) 
        {
            printf(RED "warning: too many arguments for push" DELETE_COLOR);
        }
        else if ( kolvo_arg == 3 )
        {
            GetRegister( output, input, instruction );
            output->ip += 1;
        }
        else if ( kolvo_arg == 4)
        {
            printf(RED "wrong command, maybe you ment 'OUT' ?\n" DELETE_COLOR);
        }

        ON_DEBUG
        (
            printf("\n");
            BinaryCharOutput( *instruction );
            printf("\n");
        )
    }
    
    return 0;
    
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


void BinaryCharOutput(unsigned char number)
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
