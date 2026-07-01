#ifndef ARG_H
#define ARG_H

#include "common.h"
#include "errors.h"

#define FILENAME_LEN 100

typedef struct
{
    char filename[FILENAME_LEN];
} AppArgs;

AppArgs AppArgsCreate(void);
ErrorCode AppArgsParse(AppArgs &args, const int argc, char **argv);

#endif