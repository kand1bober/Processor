#define PRINT_DEBUG


#include <string.h>
// #include <ctype.h>

#include "../Headers/asm_library.h"
#include "../Headers/asm_functions.h"
#include "../Headers/asm_decoration.h"
#include "../Headers/asm_macros.h"


void LabelTableCtor(struct Label_table* spisok)
{
    spisok->labels = (Label*)calloc(LABEL_ARR_SIZE, sizeof(Label) );
}


void LabelTableDtor(struct Label_table* spisok)
{
    free(spisok->labels);
}


void FindLabels(struct Label_table* spisok, struct File_asm* file)
{
    printf(GREEN "==Preprocessing labelss==\n" DELETE_COLOR);

    spisok->amount = 1;
    char* ptr1 = nullptr;
    char* ptr2 = nullptr;

    for (int i = 0; i < file->lines_amount; i++)
    {
        printf("%s\n", file->lines_arr[i].start);  
 
        if ( ( ptr1 = strchr( file->lines_arr[i].start, ':' ) ) != nullptr ) 
        {
            if ( ( ptr2 = strchr( file->lines_arr[i].start, ' ' ) ) != nullptr)
            {
                ptr2 = SkipSpaces( ptr2 );
                
                WriteLabel(spisok, ptr2, strlen(ptr2) + 1 );
                ON_DEBUG( printf(YELLOW "length of second metka: %ld\n" DELETE_COLOR, strlen(ptr2) + 1); )
            }
            else 
            {
                WriteLabel(spisok, file->lines_arr[i].start, ptr1 - file->lines_arr[i].start + 2);
                ON_DEBUG( printf(YELLOW "length of first metka: %ld\n" DELETE_COLOR, ptr1 - file->lines_arr[i].start + 2 ); );
            }
        }
        else 
        {
            continue;
        }
        printf("\n");
    }

    printf(PURPLE "Result:\n" );
    printf("actual size: %d\n" DELETE_COLOR, spisok->amount);
    for (int i = 0; i < spisok->amount - 1; i++)
    {   
        printf(PURPLE "%d: %s\n" DELETE_COLOR, i, spisok->labels[i].name);
    }

    printf(GREEN "==End of preprcessing labels==\n" DELETE_COLOR);
}


int WriteLabel(struct Label_table* spisok, char* ptr, size_t length)
{
    int status = 0;

    for ( int i = 0; i < spisok->amount; i++ )
    {   
        if ( strncmp( spisok->labels[i].name, ptr, length ) == 0 )
        {
            status = 0;
            break;
        }
        else 
        {
            status = 1;
            continue;
        }
    }

    if( status )
    {
        for ( int i = 0; i < spisok->amount; i++ )
        {
            if ( strlen( spisok->labels[i].name) == 0 )
            {
                snprintf(spisok->labels[i].name, length, "%s", ptr);
                spisok->amount++;
                return 1;
            }
            else
            {
                continue;
            }
        }
    }
    else 
    {
        return 0;
    }

    return -2; // kakoyto pizdec
}


// int SearchLabel( struct Label_table* spisok, char* ptr,  size_t )
// {

// }


char* SkipSpaces(char* ptr)
{
    int i = 0;
    while( *(ptr + i) == ' ')
    {
        i++;
    }
    return ptr + i;
}
