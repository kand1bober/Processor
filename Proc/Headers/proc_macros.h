
#ifndef PROC_MACROS_HEADER
#define PROC_MACROS_HEADER


#ifdef DEBUG

    #define ON_DEBUG_PROC( expr ) expr
    #define PRINT_PROCESS( expr ) expr
    #define PAUSE getchar() 

#else 

    #define ON_DEBUG_PROC( expr ) 
    #define PRINT_PROCESS( expr )
    #define PAUSE 

#endif

#endif