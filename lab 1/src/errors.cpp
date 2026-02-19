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
    case INVALID_LINES_INDEXES:
        puts("ERROR: linex indexes goes beyond the points count");
        break;
    case INVALID_POINT_INPUT:
        puts("ERROR: invalid point input");
        break;
    case INVALID_POINT_ARR_SIZE:
        puts("ERROR: invalid point arr size input");
        break;
    case INVALID_LINE_INPUT:
        puts("ERROR: invalid line input");
        break;
    case INVALID_LINE_ARR_SIZE:
        puts("ERROR: invalid line arr size input");
        break;
    case LINE_ARR_NOT_ALLOCATED:
        puts("ERROR: line arr not allocated");
        break;
    case POINT_ARR_NOT_ALLOCATED:
        puts("ERROR: point arr not allocated");
        break;
    case FILE_NOT_OPENED:
        puts("ERROR: file not opened");
        break;
    case DIV_BY_ZERO:
        puts("ERROR: div by zero");
        break;
    case UNKNOWN_TRANSFORM:
        puts("ERROR: unknown transform");
        break;
    case UNKNOWN_ACTION:
        puts("ERROR: unknown action");
        break;
    default:
        puts("ERROR: unknown error");
        break;
    }
}
