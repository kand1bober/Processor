#include "../Headers/asm_functions.h"
#include "../Headers/asm_library.h"

int main()
{
    struct File_asm input_file = {};
    struct File_code output_file = {};


    printf("type number of file with programm\n");
    unsigned file_number = 0;
    scanf("%u", &file_number);
    
    printf("You chose:\n");
    switch( file_number )
    {
        case 1:
        {
            printf("PROGRAMM_ASM_1.txt\n"); 
            strcpy(input_file.name, "PROGRAMM_ASM_1.txt");
            strcpy(output_file.name, "PROGRAMM_CODE_1.txt"); 
            break;
        }

        case 2:
        {
            printf("PROGRAMM_ASM_2.txt\n");
            strcpy(input_file.name, "PROGRAMM_ASM_2.txt");
            strcpy(output_file.name, "PROGRAMM_CODE_2.txt"); 
            break;  
        }

        default:
        {
            break;
        }
    }

    InputFileStruct(&input_file); 

    OutputFile(&input_file, &output_file);

    free(input_file.buffer);
    free(output_file.buffer);

    free(input_file.lines_arr);

    return 0;
}
