#ifndef LINE_ARR_H
#define LINE_ARR_H

#include "line.h"

typedef struct
{
    Line *inner;
    size_t size;
} LineArr;

LineArr LineArrCreate(void);
void LineArrFree(LineArr &lines);
ErrorCode LineArrRead(LineArr &lines, FILE *f);
ErrorCode LineArrCopy(LineArr &dst, const LineArr &src);

#endif