#include "appargs.h"
#include <cstdio>
#include <cstring>

AppArgs AppArgsCreate(void)
{
    AppArgs args = {};
    return args;
}

ErrorCode AppArgsParse(AppArgs &args, int argc, char **argv)
{
    ErrorCode code = SUCCESS;
    if (argc != 2)
        code = INVALID_ARG;
    else
        strcpy(args.filename, argv[1]);
    return code;
}
