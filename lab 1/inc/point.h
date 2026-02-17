#ifndef POINT_H
#define POINT_H

#include "errors.h"
#include "transforms.h"
#include <cstdio>

typedef struct 
{
    double x;
    double y;
    double z;
} Point;

Point PointCreate(const double x, const double y, const double z);
ErrorCode PointRead(Point &point, FILE *f);

void PointAdd(Point &point1, const Point &point2);
ErrorCode PointDiv(Point &point, const double divisor);

#endif