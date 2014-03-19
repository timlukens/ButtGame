#ifndef __Included_Debug__H
#define __Included_Debug__H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GameDefines.h"

using namespace std;

#if DEBUG
    #define DBMSG(x)  stderr_log(x)
    #define STDERR(x) stderr_log(x)
#else 
    #define DBMSG(x) ;
    #define STDERR(x) ;
#endif

void stderr_log(string err);



#endif // __Included_Debug__H


