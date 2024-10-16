#include "../Headers/proc_functions.h"
#include "../Headers/proc_library.h"
#include "../../Parser/Headers/pars_library.h"

void InputFileCode(struct File_proc* file)
{
    printf("type number of file with programm\n");
    unsigned file_number = 0;
    scanf("%u", &file_number);
    
    printf("You chose:\n");
    switch( file_number )
    {
        case 1:
        {
            printf("PROGRAMM_ASM_1.txt\n"); 
            strcpy(file->name, "PROGRAMM_CODE_1.txt"); 
            break;
        }

        case 2:
        {
            printf("PROGRAMM_ASM_2.txt\n");
            strcpy(file->name, "PROGRAMM_CODE_2.txt"); 
            break;  
        }

        default:
        {       
            break;
        }
    }

    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    //====OPEN FILE AND CREATE CHAR BUFFER====TAKE AUTHOR AND SIZE_OF_CODE====
    FILE* input_file = fopen(filepath, "r");

    struct stat file_info = {};

    stat(filepath, &file_info);

    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;
    printf("size of file: %lu\n", size_of_stream);

    char* char_buffer = (char*)calloc( size_of_stream + 1, sizeof(char) );

    fseek(input_file, sizeof(char) * 0L,  SEEK_SET);
    fread( (void*)char_buffer, sizeof(char), size_of_stream, input_file);
    fclose(input_file);
   

    int position = 0;
    sscanf(char_buffer, "%s", file->author);
    position += ( strlen(file->author) + 1);
    char size_of_code_tmp[5];
    sscanf(char_buffer + position, "%s", size_of_code_tmp);

    file->size_of_code = atoi(size_of_code_tmp);
    position += ( strlen(size_of_code_tmp) + 1 );

    printf("author: %s\n", file->author);
    printf("size: %ld\n", file->size_of_code);

    //=================================================================

    file->buffer = (int*)calloc(file->size_of_code, sizeof(int) );

    for (int i = 0; i < file->size_of_code; i++)
    {
        memcpy( (void*)(file->buffer + i), (void*)(char_buffer + position + sizeof(int) * i), 4);
    }

    for (int i = 0; i < file->size_of_code; i++)
    {
        printf("[%d]: %d\n", i, *(file->buffer + i) );
    }

    free(char_buffer);
}

