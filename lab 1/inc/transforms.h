#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "stdio.h"

typedef struct
{
    double x;
    double y;
    double z;
} TransformRotation;

typedef struct
{
    double factor;
} TransformScale;

typedef struct
{
    double x;
    double y;
    double z;
} TransformShift;

typedef struct
{
    TransformShift centerShift;
    TransformShift shift;
    TransformScale scale;
    TransformRotation rotation;
} TransformModelData;

TransformShift TransformShiftInit(const double x, const double y, const double z);
TransformShift TransformShiftCreate(void);
TransformRotation TransformRotationCreate(void);
TransformScale TransformScaleCreate(void);
TransformModelData TransformModelDataCreate(void);

void TransformModelDataSetCenterShift(TransformModelData &transformModelData, const TransformShift &centerShift);
void TransformModelDataAddRotation(TransformRotation &rotation, const TransformRotation &new_rotation);
void TransformModelDataAddScale(TransformScale &scale, const TransformScale &new_scale);
void TransformModelDataAddShift(TransformShift &shift, const TransformShift &new_shift);
#endif