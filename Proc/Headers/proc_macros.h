
#ifndef PROC_MACROS_HEADER
#define PROC_MACROS_HEADER

#define DEBUG
#ifdef DEBUG

    #define ON_DEBUG_PROC( expr ) expr
    #define PAUSE getchar() 

#else 

    #define ON_DEBUG_PROC( expr ) 
    #define PAUSE 

#endif

#endif