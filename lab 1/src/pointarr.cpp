#include "pointarr.h"
#include <cstdlib>
#include <cstring>

static ErrorCode PointArrAlloc(Point **inner, const size_t size);
static Point PointArrSum(const Point *array, const size_t size);

PointArr PointArrCreate(void)
{
    PointArr points;
    points.inner = NULL;
    points.size = 0;
    return points;
}

void PointArrFree(PointArr &points)
{
    free(points.inner);
    points.inner = NULL;
    points.size = 0;
}

ErrorCode PointArrRead(PointArr &points, FILE *f)
{
    ErrorCode code = SUCCESS;
    if (f == NULL)
        code = INVALID_ARG;
    else
    {
        int tmp;
        if (fscanf(f, "%d", &tmp) != 1 || tmp <= 0)
            code = INVALID_INPUT;
        else
        {
            size_t tmpSize = (size_t) tmp;
            Point *tmpInner = NULL;
            code = PointArrAlloc(&tmpInner, tmpSize);
            for (size_t i = 0; code == SUCCESS && i < tmpSize; i++)
                code = PointRead(tmpInner[i], f);
            
            if (code != SUCCESS)
                free(tmpInner);
            else
            {
                points.inner = tmpInner;
                points.size = tmpSize;
            }
        }
    }
    return code;
}

ErrorCode PointArrCopy(PointArr &dst, const PointArr &src)
{
    ErrorCode code = SUCCESS;
    code = PointArrAlloc(&dst.inner, src.size);
    if (code == SUCCESS)
    {
        memmove(dst.inner, src.inner, sizeof(Point) * src.size);
        dst.size = src.size;
    }
    return code;
}

ErrorCode PointArrCenter(Point &center, const PointArr &points)
{
    ErrorCode code = SUCCESS;
    Point tmp = PointArrSum(points.inner, points.size);
    code = PointDiv(tmp, points.size);
    if (code == SUCCESS)
        center = tmp;
    return code;
}

static Point PointArrSum(const Point *array, const size_t size)
{
    Point pointSum = PointCreate(0, 0, 0);
    for (size_t i = 0; i < size; i++)
        PointAdd(pointSum, array[i]);
    return pointSum;
}

static ErrorCode PointArrAlloc(Point **inner, const size_t size)
{
    ErrorCode code = SUCCESS;
    if (size == 0)
        code = INVALID_ARG;
    else
    {
        Point *tmp = (Point *) calloc(sizeof(Point), size);
        if (tmp == NULL)
            code = MEMORY;
        else
            *inner = tmp;
    }
    return code;
}