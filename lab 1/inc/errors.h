#ifndef ERRORS_H
#define ERRORS_H

#include "common.h"

typedef enum
{
    SUCCESS,
    INVALID_ARG,
    INVALID_INPUT,
    MEMORY,
    FILE_NOT_OPENED,
    DIV_BY_ZERO
} ErrorCode;

void ErrorPrint(const ErrorCode code);

#endif