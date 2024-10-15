#include <string.h>
#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"
#include "../../Parser/Headers/pars_library.h"

//=====CONVERT TO CODE AND WRITE IN OUTPUT======
void OutputFile(struct File_asm* file_a, struct File_code* file_b)
{
    // printf("1\n");
    for(int i = 0; i < file_a->size_of_file; i++)
    {
        if ( file_a->buffer[i] == '\n' )
        {
            file_a->buffer[i] = '\0';
            (file_a->size_of_code)++;
        }
    }
    file_a->size_of_code++;

    // printf("2\n");
    file_b->buffer = (int*)calloc(file_a->size_of_code, sizeof(int) );

    // printf("3\n");
    
    int out_count = 0;
    for(int in_count = 0; in_count < file_a->size_of_file; out_count++, in_count++)
    {
        char command[20] = {};
        sscanf(file_a->buffer + in_count, "%s", command);

        if ( strcmp(command, "push") == 0)
        {
            printf("push : %d\n", kPush);
            file_b->buffer[out_count] = kPush;
            out_count++;
            in_count += 5;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);

            printf("%s\n", file_a->buffer + in_count);
            printf("lenght: %ld\n", strlen(file_a->buffer + in_count) );

            in_count += ( strlen(file_a->buffer + in_count) );
            continue;
        }

        if ( strcmp(command, "out") == 0 )
        {
            file_b->buffer[out_count] = kOut;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "add") == 0 )
        {
            file_b->buffer[out_count] = kAdd;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "in") == 0 )
        {
            file_b->buffer[out_count] = kIn;
            in_count += 2;
            continue;
        }

        if ( strcmp(command, "sub") == 0 )
        {
            file_b->buffer[out_count] = kSub;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "mul") == 0 )
        {
            file_b->buffer[out_count] = kMul;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "div") == 0 )
        {
            file_b->buffer[out_count] = kDiv;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "root") == 0 )
        {
            file_b->buffer[out_count] = kRoot;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "sin") == 0 )
        {
            file_b->buffer[out_count] = kSin;
            in_count += 3;
            continue;
        }

        if ( strcmp(command, "cos") == 0 )
        {
            file_b->buffer[out_count] = kCos;
            in_count += 3;
            continue;
        }
        
        if ( strcmp(command, "dump") == 0 )
        {
            file_b->buffer[out_count] = kDump;
            in_count += 4;
            continue;
        }

        if ( strcmp(command, "hlt") == 0 )
        {
            file_b->buffer[out_count] = kHlt;
            in_count += 3;
            break;
        }

        //===========JUMPS===============
        if ( strcmp(command, "ja") == 0 )
        {
            file_b->buffer[out_count] = kJa;
            out_count++;
            in_count += 3;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
            continue;
        }

        if ( strcmp(command, "jae") == 0 )
        {
            file_b->buffer[out_count] = kJa;
            out_count++;
            in_count += 4;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
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
    // printf("4\n");
    
    file_b->size_of_code = out_count;
}
//==============================================

