#include "transforms.h"

static void TransformModelDataAddShift(VAR TransformShift &shift, IN const TransformShift &new_shift);
static void TransformModelDataAddScale(VAR TransformScale &scale, IN const TransformScale &new_scale);
static void TransformModelDataAddRotation(VAR TransformRotation &rotation, IN const TransformRotation &new_rotation);

TransformShift TransformShiftInit(IN const double x, IN const double y, IN const double z)
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

void TransformModelDataSetCenterShift(VAR TransformModelData &transformModelData, IN const TransformShift &centerShift)
{
    transformModelData.centerShift = centerShift;
}

ErrorCode TransformModelDataUpdate(VAR TransformModelData &transformModelData, IN const Transforms &transforms)
{
    ErrorCode code = SUCCESS;
    switch (transforms.type)
    {
    case ROTATE:
        TransformModelDataAddRotation(transformModelData.rotation, transforms.rotation);
        break;
    case SHIFT:
        TransformModelDataAddShift(transformModelData.shift, transforms.shift);
        break;
    case SCALE:
        TransformModelDataAddScale(transformModelData.scale, transforms.scale);
        break;
    default:
        code = UNKNOWN_TRANSFORM;
        break;
    }
    return code;
}

void TransoformsSetRotation(VAR Transforms &transforms, IN const TransformRotation &rotation)
{
    transforms.type = ROTATE;
    transforms.rotation = rotation;
}

void TransoformsSetShift(VAR Transforms &transforms, IN const TransformShift &shift)
{
    transforms.type = SHIFT;
    transforms.shift = shift;
}

void TransoformsSetScale(VAR Transforms &transforms, IN const TransformScale &scale)
{
    transforms.type = SCALE;
    transforms.scale = scale;
}

static void TransformModelDataAddShift(VAR TransformShift &shift, IN const TransformShift &new_shift)
{
    shift.x += new_shift.x;
    shift.y += new_shift.y;
    shift.z += new_shift.z;
}

static void TransformModelDataAddScale(VAR TransformScale &scale, IN const TransformScale &new_scale)
{
    scale.factor *= new_scale.factor;
}

static void TransformModelDataAddRotation(VAR TransformRotation &rotation, IN const TransformRotation &new_rotation)
{
    rotation.x += new_rotation.x;
    rotation.y += new_rotation.y;
    rotation.z += new_rotation.z;
}