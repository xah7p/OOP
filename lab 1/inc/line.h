#ifndef LINE_H
#define LINE_H

#include "common.h"
#include "errors.h"
#include <stdio.h>

typedef struct
{
    size_t startIndex;
    size_t endIndex;
} Line;

Line LineCreate(const size_t start, const size_t end);
ErrorCode LineRead(Line &line, FILE *f);

#endif