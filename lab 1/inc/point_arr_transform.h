#ifndef POINT_ARR_TRANSFORM_H
#define POINT_ARR_TRANSFORM_H

#include "pointarr.h"
#include "transforms.h"

void PointArrRotateAroundCenter(PointArr &points, const TransformRotation &rotation);
void PointArrScale(PointArr &points, const TransformScale &rotation);
void PointArrShift(PointArr &points, const TransformShift &shift);

#endif
