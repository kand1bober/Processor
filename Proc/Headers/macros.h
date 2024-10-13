
#ifndef PROC_MACROS_HEADER
#define PROC_MACROS_HEADER

#define DEBUG
#ifdef DEBUG

#define ON_DEBUG( expr ) expr
#define PAUSE ( getchar() )

#endif

#endif