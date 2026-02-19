#include "pointarr.h"
#include <cstdlib>
#include <cstring>

static ErrorCode PointArrAlloc(VAR Point **inner, IN const size_t size);
static Point PointArrSum(IN const Point *array, IN const size_t size);

PointArr PointArrCreate(void)
{
    PointArr points;
    points.inner = NULL;
    points.size = 0;
    return points;
}

void PointArrFree(VAR PointArr &points)
{
    free(points.inner);
    points.inner = NULL;
    points.size = 0;
}

ErrorCode PointArrRead(OUT PointArr &points, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;

    ErrorCode code = SUCCESS;
    if (fscanf(f, "%zu", &points.size) != 1)
        code = INVALID_INPUT;
    else
    {
        code = PointArrAlloc(&points.inner, points.size);
        for (size_t i = 0; code == SUCCESS && i < points.size; i++)
            code = PointRead(points.inner[i], f);
        
        if (code != SUCCESS)
            free(points.inner);
    }
    return code;
}

ErrorCode PointArrCopy(OUT PointArr &dst, IN const PointArr &src)
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

ErrorCode PointArrCenter(OUT Point &center, IN const PointArr &points)
{
    ErrorCode code = SUCCESS;
    center = PointArrSum(points.inner, points.size);
    code = PointDiv(center, points.size);
    return code;
}

static Point PointArrSum(IN const Point *array, IN const size_t size)
{
    Point pointSum = PointCreate(0, 0, 0);
    for (size_t i = 0; i < size; i++)
        PointAdd(pointSum, array[i]);
    return pointSum;
}

static ErrorCode PointArrAlloc(VAR Point **inner, IN const size_t size)
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