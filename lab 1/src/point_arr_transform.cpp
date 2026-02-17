#include "point_arr_transform.h"
#include "point_transform.h"

void PointArrScale(PointArr &points, const TransformScale &scale)
{
    for (size_t i = 0; i < points.size; i++)
        PointScale(points.inner[i], scale);
}

void PointArrShift(PointArr &points, const TransformShift &shift)
{
    for (size_t i = 0; i < points.size; i++)
        PointShift(points.inner[i], shift);
}

void PointArrRotate(PointArr &points, const TransformRotation &rotation)
{
    for (size_t i = 0; i < points.size; i++)
        PointRotate(points.inner[i], rotation);
}

void PointArrRotateAroundCenter(PointArr &points, const TransformRotation &rotation)
{
    Point barycenter = PointCreate(0, 0, 0);

    if (PointArrCenter(barycenter, points) == SUCCESS)
    {
        TransformShift shift_back = TransformShiftInit(-barycenter.x, -barycenter.y, -barycenter.z);
        TransformShift shift_front = TransformShiftInit(barycenter.x, barycenter.y, barycenter.z);

        PointArrShift(points, shift_back);
        PointArrRotate(points, rotation);
        PointArrShift(points, shift_front);
    }
}