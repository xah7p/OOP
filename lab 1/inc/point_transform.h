#ifndef POINT_TRANSFORM_H
#define POINT_TRANSFORM_H

#include "point.h"
#include "transforms.h"

void PointRotate(Point &point, const TransformRotation &rotation);
void PointScale(Point &point, const TransformScale &scale);
void PointShift(Point &point, const TransformShift &shift);

#endif