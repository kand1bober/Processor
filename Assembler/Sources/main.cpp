

#include "../Headers/functions.h"
#include "../Headers/library.h"

int main()
{
    struct File_asm input_file = {};
    struct File_code output_file = {};


    printf("type number of file with programm\n");
    unsigned file_number = 0;
    scanf("%u", &file_number);


    switch( file_number )
    {
        case 1:
        {
            input_file.name = "PROGRAMM_ASM_1.txt";
            output_file.name = "PROGRAMM_CODE_1.txt"
            break;
        }

        case 2:
        {
            input_file.name = "PROGRAMM_ASM_2.txt";
            output_file.name = "PROGRAMM_CODE_2.txt";
            break;  
        }

        default:
        {
            break;
        }
    }

    InputFileStruct(input_file.name);
    char* input_buffer = input_file.buffer;    


    CharToIntAndStruct (&input_file );

    OutputFile(output_file, );

    
    free(input_buffer);

    return 0;
}
