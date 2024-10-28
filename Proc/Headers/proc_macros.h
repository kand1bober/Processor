
#ifndef PROC_MACROS_HEADER
#define PROC_MACROS_HEADER


    #ifdef DEBUG

        #define ON_DEBUG_PROC( expr ) expr
        #define PRINT_PROCESS( expr ) expr

    #else 

        #define ON_DEBUG_PROC( expr ) 
        #define PRINT_PROCESS( expr )
        
    #endif


    #ifdef STEP
        #define PAUSE getchar() 
    #else       
        #define PAUSE 
    #endif


    #ifdef RUN_PROC
        #define RUN( expr ) expr
    #else       
        #define RUN( expr )
    #endif
     

#endif
