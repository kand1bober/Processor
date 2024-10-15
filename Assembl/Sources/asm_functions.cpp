#include "../Headers/asm_library.h"

//=====CONVERT TO CODE AND WRITE IN OUTPUT======
void OutputFile(struct File_asm* file_a, struct File_code* file_b)
{
    for(int i = 0; i < file_a->size_of_file; i++)
    {
        if( (file_a->buffer[i] == '\n') ||  (file_a->buffer[i] == ' ') )
        {
            file_a->buffer[i] = '\0';
            (file_a->size_of_code)++;
        }
    }
    file_a->size_of_code++;


    file_b->buffer = (int*)calloc(file_a->size_of_code, sizeof(int) );
    int* code_buffer = file_b->buffer;

    for(int in_count = 0, out_count; in_count < file_a->size_of_file; out_count++)
    {
        char command[20] = {};
        sscanf(file_a->buffer, "%s", command);

        if ( strcmp(command, "push") == 0)
        {
            code_buffer[out_count] = kPush;
            out_count++;
            in_count += 5;
            code_buffer[out_count] = atoi(file_a->buffer + in_count);
            continue;
        }

        if ( strcmp(command, "out") == 0 )
        {
            code_buffer[out_count] = kOut;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "add") == 0 )
        {
            code_buffer[out_count] = kAdd;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "in") == 0 )
        {
            code_buffer[out_count] = kIn;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "sub") == 0 )
        {
            code_buffer[out_count] = kSub;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "mul") == 0 )
        {
            code_buffer[out_count] = kMul;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "div") == 0 )
        {
            code_buffer[out_count] = kDiv;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "root") == 0 )
        {
            code_buffer[out_count] = kRoot;
            in_count += 5;
            continue;
        }

        if ( strcmp(command, "sin") == 0 )
        {
            code_buffer[out_count] = kSin;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "cos") == 0 )
        {
            code_buffer[out_count] = kCos;
            in_count += 4;
            continue;
        }
        
        if ( strcmp(command, "dump") == 0 )
        {
            code_buffer[out_count] = kDump;
            in_count += 5;
            continue;
        }

        if ( strcmp(command, "hlt") == 0 )
        {
            code_buffer[out_count] = kHlt;
            in_count += 4;
            break;
        }

        //===========JUMPS===============
        if ( strcmp(command, "ja") == 0 )
        {
            code_buffer[out_count] = kJa;
            out_count++;
            in_count += 3;
            code_buffer[out_count] = atoi(file_a->buffer + in_count);
            continue;
        }

        if ( strcmp(command, "jae") == 0 )
        {
            code_buffer[out_count] = kJa;
            out_count++;
            in_count += 4;
            code_buffer[out_count] = atoi(file_a->buffer + in_count);
            continue;
        }

        // if ( strcmp(command, "jb") == 0 )
        // {
            
        // }

        // if ( strcmp(command, "jbe") == 0 )
        // {
            
        // }

        // if ( strcmp(command, "je") == 0 )
        // {
            
        // }
        // if ( strcmp(command, "jne") == 0 )
        // {
            
        // }

        // if ( strcmp(command, "jmp") == 0 )
        // {
            
        // }
        //=========END_OF_JUMPS===============

        // if ( strcmp(command, "pushr") == 0 )
        // {
            
        // }

        // if ( strcmp(command, "outr") == 0 )
        // {
            
        // }
    }
}
//==============================================

