#include <string.h>
#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"

//=====CONVERT TO CODE AND WRITE IN OUTPUT======

// TODO: input.cpp
void OutputFile(struct File_asm* file_a, struct File_code* file_b)
{
    file_b->buffer = (int*)calloc(file_a->size_of_code, sizeof(AssemblerElem) );

    int out_count = 0;

    // file_a->bitwise_buffer = (char*)calloc( file_a->size_of_code, sizeof(char) );


    // while(1)
    // {

    // }








    //=========GET_FILEPATH=========================
    const char* directory = "/home/vyacheslav/Processor/";
    const char* filename = file_b->name;
    char filepath[200] = {};
    sprintf(filepath, "%s%s", directory, filename);
    //==============================================

    FILE* output_stream = fopen(filepath, "wb");
    printf("Position in File: %ld\n", ftell(output_stream) );

    // file_b->head.size_of_code = ;
    file_b->head.sign = SIGNATURE;
    file_b->head.ver = VERSION;

    fwrite(&file_b->head, 1, sizeof(file_b->head), output_stream);
    fwrite(file_b->buffer, file_b->head.size_of_code, sizeof(int), output_stream);
    fclose(output_stream);
}
//==============================================


