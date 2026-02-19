#include "line.h"

Line LineCreate(IN const size_t start, IN const size_t end)
{
    Line line = {start, end};
    return line;
}

ErrorCode LineRead(VAR Line &line, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;
        
    ErrorCode rc = SUCCESS;
    int tmpStartIndex, tmpEndIndex;
    if (fscanf(f, "%d%d", &tmpStartIndex, &tmpEndIndex) != 2 || tmpStartIndex < 0 || tmpEndIndex < 0 || tmpStartIndex == tmpEndIndex)
        rc = INVALID_LINE_INPUT;
    else
        line = LineCreate((size_t) tmpStartIndex, (size_t) tmpEndIndex);
    return rc;
}