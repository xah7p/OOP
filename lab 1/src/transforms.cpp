#include "transforms.h"

TransformShift TransformShiftInit(const double x, const double y, const double z)
{
    TransformShift shift = {x, y, z};
    return shift;
}

TransformShift TransformShiftCreate(void)
{
    TransformShift shift = {0, 0, 0};
    return shift;
}

TransformScale TransformScaleCreate(void)
{
    TransformScale scale = {1};
    return scale;
}

TransformRotation TransformRotationCreate(void)
{
    TransformRotation rotation = {0, 0, 0};
    return rotation;
}

TransformModelData TransformModelDataCreate(void)
{
    TransformModelData transformModelData = {TransformShiftCreate(), TransformShiftCreate(), 
                    TransformScaleCreate(), TransformRotationCreate()};
    return transformModelData;
}

void TransformModelDataSetCenterShift(TransformModelData &transformModelData, const TransformShift &centerShift)
{
    transformModelData.centerShift = centerShift;
}

void TransformModelDataAddShift(TransformShift &shift, const TransformShift &new_shift)
{
    shift.x += new_shift.x;
    shift.y += new_shift.y;
    shift.z += new_shift.z;
}

void TransformModelDataAddScale(TransformScale &scale, const TransformScale &new_scale)
{
    scale.factor *= new_scale.factor;
}

void TransformModelDataAddRotation(TransformRotation &rotation, const TransformRotation &new_rotation)
{
    rotation.x += new_rotation.x;
    rotation.y += new_rotation.y;
    rotation.z += new_rotation.z;
}
