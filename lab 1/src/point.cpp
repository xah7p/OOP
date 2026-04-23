#include "point.h"

Point PointCreate(IN const double x, IN const double y, IN const double z)
{
    Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    return point;
}

ErrorCode PointRead(VAR Point &point, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;

    ErrorCode rc = SUCCESS;
    Point pointTemp;
    if (fscanf(f, "%lf%lf%lf", &pointTemp.x, &pointTemp.y, &pointTemp.z) != 3)
        rc = INVALID_POINT_INPUT;
    else
        point = pointTemp;
    return rc;
}

void PointAdd(VAR Point &point1, IN const Point &point2)
{
    point1.x += point2.x;
    point1.y += point2.y;
    point1.z += point2.z;
}

ErrorCode PointDiv(VAR Point &point, IN const double divisor)
{
    if (divisor == 0)
        return DIV_BY_ZERO;
        
    point.x /= divisor;
    point.y /= divisor;
    point.z /= divisor;
    return SUCCESS;
}