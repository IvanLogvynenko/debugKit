#include <iostream>

#ifndef EXECUTABLE_NAME
    #define EXECUTABLE_NAME "UNNAMED"
#endif // !EXECUTABLE_NAME

#ifdef LOGGING
    #define ILOG(x) std::cout << " [ IMPORTANT ] [ " << EXECUTABLE_NAME << " ] : " << x << "\n"; 
#else
    #define ILOG(x)
#endif // DEBUG 

#ifdef FULL_LOGGING
    #define  LOG(x) std::cout << "               [ " << EXECUTABLE_NAME << " ] : " << x << "\n"; 
#else
    #define LOG(x)
#endif // FULL_LOGGING

#ifdef ERROR
    #define  EL(x) std::cerr << "  [   ERROR   ] [ " << EXECUTABLE_NAME << " ] : " << x << "\n"; 
#else
    #define EL(x)
#endif // ERROR
