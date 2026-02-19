#include "errors.h"
#include <cstdio>

void ErrorPrint(IN const ErrorCode code)
{
    switch (code)
    {
    case SUCCESS:
        break;
    case INVALID_ARG:
        puts("ERROR: invalid argurments");
        break;
    case INVALID_INPUT:
        puts("ERROR: invalid input");
        break;
    case MEMORY:
        puts("ERROR: memory");
        break;
    case FILE_NOT_OPENED:
        puts("ERROR: file not opened");
        break;
    case DIV_BY_ZERO:
        puts("ERROR: div by zero");
        break;
    }
}
