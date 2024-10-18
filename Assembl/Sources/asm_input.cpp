#include "../Headers/asm_functions.h"

//======READING TO THE char* BUFFER=======
void InputFileStruct(struct File_asm* file)
{
    // printf("name: %s\n", file->name);

    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    FILE* stream = fopen(filepath, "r");

    // printf("pointer: %p\n", stream);

    struct stat file_info = {};

    stat(filepath, &file_info);

    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;
    printf("size of file: %lu\n", size_of_stream);

    file->size_of_file = size_of_stream;

    file->buffer = (char*)calloc( size_of_stream + 1, sizeof(char) );

    fseek(stream, sizeof(char) * 0L,  SEEK_SET);
    fread( (void*)file->buffer, sizeof(char), size_of_stream, stream);
    
    fclose(stream);
    
    printf("Your file:\n\n%s\n\n", file->buffer);
}
//===============================================

