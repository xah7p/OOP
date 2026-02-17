#include "linearr.h"
#include <cstdlib>
#include <cstring>

static ErrorCode LineArrAlloc(Line **inner, const size_t size);

LineArr LineArrCreate(void)
{
    LineArr lines;
    lines.inner = NULL;
    lines.size = 0;
    return lines;
}

void LineArrFree(LineArr &lines)
{
    free(lines.inner);
    lines.inner = NULL;
    lines.size = 0;
}

ErrorCode LineArrRead(LineArr &lines, FILE *f)
{
    ErrorCode code = SUCCESS;
    if (f == NULL)
        return INVALID_ARG;

    int tmp;
    if (fscanf(f, "%d", &tmp) != 1 || tmp <= 0)
        code = INVALID_INPUT;
    else
    {
        size_t tmpSize = (size_t) tmp;
        Line *tmpInner = NULL;
        code = LineArrAlloc(&tmpInner, tmpSize);
        for (size_t i = 0; code == SUCCESS && i < tmpSize; i++)
            code = LineRead(tmpInner[i], f);
        
        if (code != SUCCESS)
            free(tmpInner);
        else
        {
            lines.inner = tmpInner;
            lines.size = tmpSize;
        }
    }
    return code;
}

ErrorCode LineArrCopy(LineArr &dst, const LineArr &src)
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

static ErrorCode LineArrAlloc(Line **inner, const size_t size)
{
    ErrorCode rc = SUCCESS;
    if (size == 0)
        rc = INVALID_ARG;
    else
    {
        Line *tmp = (Line *) calloc(sizeof(Line), size);
        if (tmp == NULL)
            rc = MEMORY;
        else
            *inner = tmp;
    }
    return rc;
}