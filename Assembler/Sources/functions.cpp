

#include "../Headers/library.h"
#include "../Headers/library.h"

void InputFileStruct(struct File_asm* file)
{
    FILE* stream = fopen(file->name, "r");

    struct stat file_info = {};

    stat(file->name, &file_info);

    unsigned long int size_of_stream = (unsigned long int)file_info.st_size;

    file->size = size_of_stream;

    char* buffer = (char*)calloc( size_of_stream, sizeof(char) );

    fseek(stream, sizeof(char) * 0L,  SEEK_SET);
    fread(file->buffer, sizeof(char), size_of_stream, stream);
}

void OutputFile(struct File_code* file)
{
    file.author = "KVV";


}