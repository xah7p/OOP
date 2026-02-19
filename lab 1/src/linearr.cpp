#include "linearr.h"
#include <cstdlib>
#include <cstring>

static ErrorCode LineArrAlloc(VAR Line **inner, IN const size_t size);

LineArr LineArrCreate(void)
{
    LineArr lines;
    lines.inner = NULL;
    lines.size = 0;
    return lines;
}

void LineArrFree(VAR LineArr &lines)
{
    free(lines.inner);
    lines.inner = NULL;
    lines.size = 0;
}

ErrorCode LineArrRead(OUT LineArr &lines, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;

    ErrorCode code = SUCCESS;
    if (fscanf(f, "%zu", &lines.size) != 1)
        code = INVALID_INPUT;
    else
    {
        code = LineArrAlloc(&lines.inner, lines.size);
        for (size_t i = 0; code == SUCCESS && i < lines.size; i++)
            code = LineRead(lines.inner[i], f);
        
        if (code != SUCCESS)
            free(lines.inner);
    }
    return code;
}

ErrorCode LineArrCopy(OUT LineArr &dst, IN const LineArr &src)
{
    ErrorCode code = SUCCESS;
    code = LineArrAlloc(&dst.inner, src.size);
    if (code == SUCCESS)
    {
        memmove(dst.inner, src.inner, sizeof(Line) * src.size);
        dst.size = src.size;
    }
    return code;
}

static ErrorCode LineArrAlloc(VAR Line **inner, IN const size_t size)
{
    if (size == 0)
        return INVALID_ARG;
    
    ErrorCode rc = SUCCESS;
    Line *tmp = (Line *) calloc(sizeof(Line), size);
    if (tmp == NULL)
        rc = MEMORY;
    else
        *inner = tmp;
    return rc;
}