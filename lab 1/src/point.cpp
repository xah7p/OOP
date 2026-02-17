#include "point.h"

Point PointCreate(const double x, const double y, const double z)
{
    Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    return point;
}

ErrorCode PointRead(Point &point, FILE *f)
{
    ErrorCode rc = SUCCESS;
    if (f == NULL)
        rc = INVALID_ARG;
    else
    {
        Point pointTemp;
        if (fscanf(f, "%lf%lf%lf", &pointTemp.x, &pointTemp.y, &pointTemp.z) != 3)
            rc = INVALID_INPUT;
        else
            point = pointTemp;
    }
    return rc;
}

void PointAdd(Point &point1, const Point &point2)
{
    point1.x += point2.x;
    point1.y += point2.y;
    point1.z += point2.z;
}

ErrorCode PointDiv(Point &point, const double divisor)
{
    ErrorCode code = SUCCESS;
    if (divisor == 0)
        code = DIV_BY_ZERO;
    else
    {
        point.x /= divisor;
        point.y /= divisor;
        point.z /= divisor;
    }
    return code;
}