#include "point_transform.h"
#include "transforms.h"
#include <cmath>

static void PointRotateX(Point &point, const double &angle);
static void PointRotateY(Point &point, const double &angle);
static void PointRotateZ(Point &point, const double &angle);

void PointScale(Point &point, const TransformScale &scale)
{
    point.x *= scale.factor;
    point.y *= scale.factor;
    point.z *= scale.factor;
}

void PointShift(Point &point, const TransformShift &shift)
{
    point.x += shift.x;
    point.y += shift.y;
    point.z += shift.z;
}

void PointRotate(Point &point, const TransformRotation &rotation)
{
    PointRotateX(point, rotation.x);
    PointRotateY(point, rotation.y);
    PointRotateZ(point, rotation.z);
}

static void PointRotateX(Point &point, const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double y = cosAngle * point.y + sinAngle * point.z;
    double z = -sinAngle * point.y + cosAngle * point.z;

    point.y = y;
    point.z = z;
}

static void PointRotateY(Point &point, const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double x = cosAngle * point.x - sinAngle * point.z;
    double z = sinAngle * point.x + cosAngle * point.z;

    point.x = x;
    point.z = z;
}

static void PointRotateZ(Point &point, const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double x = cosAngle * point.x + sinAngle * point.y;
    double y = -sinAngle * point.x + cosAngle * point.y;

    point.x = x;
    point.y = y;
}
