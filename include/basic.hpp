#include <iostream>

#ifndef EXECUTABLE_NAME
    #define EXECUTABLE_NAME "UNNAMED"
#endif // !EXECUTABLE_NAME

#ifdef DEBUG
    #define ILOG(x) std::cout << ">>> " << EXECUTABLE_NAME << " >>> " << x << "\n"; 
    #ifdef ERROR
        #define  EL(x) std::cerr << ">>> " << EXECUTABLE_NAME << " >>> " << x << "\n"; 
    #else
        #define EL(x)
    #endif // ERROR
#else
    #define ILOG(x)
#endif // DEBUG 

#ifdef FULL_LOGGING
    #define  LOG(x) std::cout << "    " << EXECUTABLE_NAME << "  >  " << x << "\n"; 
#else
    #define LOG(x)
#endif // FULL_LOGGING

