#include "appargs.h"
#include <cstdio>
#include <cstring>

AppArgs AppArgsCreate(void)
{
    AppArgs args = {};
    return args;
}

ErrorCode AppArgsParse(VAR AppArgs &args, IN const int argc, IN char **argv)
{
    if (argc != 2)
        return INVALID_ARG;
        
    strcpy(args.filename, argv[1]);
    return SUCCESS;
}
