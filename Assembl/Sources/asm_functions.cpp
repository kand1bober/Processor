#include <string.h>
#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"

//=====CONVERT TO CODE AND WRITE IN OUTPUT======
void OutputFile(struct File_asm* file_a, struct File_code* file_b)
{
    for(int i = 0; i < file_a->size_of_file; i++)
    {
        if ( (file_a->buffer[i] == '\n') || (file_a->buffer[i] == ' ') )
        {
            file_a->buffer[i] = '\0';
            (file_a->size_of_code)++;
        }
    }

    printf("size of code in struct of input: %d\n", file_a->size_of_code);
    file_b->buffer = (int*)calloc(file_a->size_of_code, sizeof(AssemblerElem) );

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
            in_count += strlen(command);
            in_count++;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);

            printf("%s\n", file_a->buffer + in_count);
            printf("lenght: %ld\n", strlen(file_a->buffer + in_count) );

            in_count += ( strlen(file_a->buffer + in_count) );
            continue;
        }

        if ( strcmp(command, "out") == 0 )
        {
            file_b->buffer[out_count] = kOut;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "add") == 0 )
        {
            file_b->buffer[out_count] = kAdd;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "in") == 0 )
        {
            file_b->buffer[out_count] = kIn;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "sub") == 0 )
        {
            file_b->buffer[out_count] = kSub;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "mul") == 0 )
        {
            file_b->buffer[out_count] = kMul;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "div") == 0 )
        {
            file_b->buffer[out_count] = kDiv;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "root") == 0 )
        {
            file_b->buffer[out_count] = kRoot;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "sin") == 0 )
        {
            file_b->buffer[out_count] = kSin;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "cos") == 0 )
        {
            file_b->buffer[out_count] = kCos;
            in_count += strlen(command) ;
            continue;
        }
        
        if ( strcmp(command, "dump") == 0 )
        {
            file_b->buffer[out_count] = kDump;
            in_count += strlen(command) ;
            continue;
        }

        if ( strcmp(command, "hlt") == 0 )
        {
            file_b->buffer[out_count] = kHlt;
            in_count += strlen(command);

            out_count++; //leaves the cucle without an increment --> invalid size
            break;
        }

        //===========JUMPS===============
        if ( strcmp(command, "ja") == 0 )
        {
            file_b->buffer[out_count] = kJa;
            out_count++;
            in_count += strlen(command);
            in_count++;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
            in_count += strlen(file_a->buffer + in_count);
            continue;
        }

        if ( strcmp(command, "jae") == 0 )
        {
            file_b->buffer[out_count] = kJa;
            out_count++;
            in_count += strlen(command);
            in_count++;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
            in_count += strlen(file_a->buffer + in_count);
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

        if ( strcmp(command, "pushr") == 0 )
        {
            file_b->buffer[out_count] = kPushR;
            out_count++;
            in_count += strlen(command);
            in_count++;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
            in_count += strlen(file_a->buffer + in_count);
            continue;
        }

        if ( strcmp(command, "outr") == 0 )
        {
            file_b->buffer[out_count] = kOutR;
            out_count++;
            in_count += strlen(command);
            in_count++;
            file_b->buffer[out_count] = atoi(file_a->buffer + in_count);
            in_count += strlen(file_a->buffer + in_count);
            continue;
        }
    }
    file_b->head.size_of_code = out_count;    

    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file_b->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    FILE* output_stream = fopen(filepath, "wb");
    // strcpy(file_b->author, "KVV");
    // fprintf(output_stream, "%s%c%d%c", file_b->author, '\0', file_b->size_of_code, '\0');
    printf("Position in File: %ld\n", ftell(output_stream) );

    file_b->head.sign = SIGNATURE;
    file_b->head.ver = VERSION;

    fwrite(&file_b->head, 1, sizeof(file_b->head), output_stream);
    fwrite(file_b->buffer, file_b->head.size_of_code, sizeof(int), output_stream);
    // fwrite( (void*)file_b->buffer, file_b->size_of_code, sizeof(AssemblerElem), output_stream);
    fclose(output_stream);
}
//==============================================


