#include "point_transform.h"
#include "transforms.h"
#include <cmath>

static void PointRotateX(VAR Point &point, IN const double &angle);
static void PointRotateY(VAR Point &point, IN const double &angle);
static void PointRotateZ(VAR Point &point, IN const double &angle);

void PointScale(VAR Point &point, IN const TransformScale &scale)
{
    point.x *= scale.factor;
    point.y *= scale.factor;
    point.z *= scale.factor;
}

void PointShift(VAR Point &point, IN const TransformShift &shift)
{
    point.x += shift.x;
    point.y += shift.y;
    point.z += shift.z;
}

void PointRotate(VAR Point &point, IN const TransformRotation &rotation)
{
    PointRotateX(point, rotation.x);
    PointRotateY(point, rotation.y);
    PointRotateZ(point, rotation.z);
}

static void PointRotateX(VAR Point &point, IN const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double y = cosAngle * point.y + sinAngle * point.z;
    double z = -sinAngle * point.y + cosAngle * point.z;

    point.y = y;
    point.z = z;
}

static void PointRotateY(VAR Point &point, IN const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double x = cosAngle * point.x - sinAngle * point.z;
    double z = sinAngle * point.x + cosAngle * point.z;

    point.x = x;
    point.z = z;
}

static void PointRotateZ(VAR Point &point, IN const double &angle)
{
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double x = cosAngle * point.x + sinAngle * point.y;
    double y = -sinAngle * point.x + cosAngle * point.y;

    point.x = x;
    point.y = y;
}
