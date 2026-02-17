#include "line.h"

Line LineCreate(const size_t start, const size_t end)
{
    Line line = {start, end};
    return line;
}

ErrorCode LineRead(Line &line, FILE *f)
{
    {
    ErrorCode rc = SUCCESS;
    if (f == NULL)
        rc = INVALID_ARG;
    else
    {
        int tmpStartIndex, tmpEndIndex;
        if (fscanf(f, "%d%d", &tmpStartIndex, &tmpEndIndex) != 2 || tmpStartIndex < 0 || tmpEndIndex < 0 || tmpStartIndex == tmpEndIndex)
            rc = INVALID_INPUT;
        else
            line = LineCreate((size_t) tmpStartIndex, (size_t) tmpEndIndex);
    }
    return rc;
}
}