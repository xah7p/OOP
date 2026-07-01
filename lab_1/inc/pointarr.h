#ifndef POINT_ARR_H
#define POINT_ARR_H

#include "common.h"
#include "point.h"

typedef struct
{
    Point *inner;
    size_t size;
} PointArr;

PointArr PointArrCreate(void);
void PointArrFree(PointArr &points);
ErrorCode PointArrRead(PointArr &points, FILE *f);
ErrorCode PointArrCopy(PointArr &dst, const PointArr &src);
ErrorCode PointArrCenter(Point &center, const PointArr &points);

#endif