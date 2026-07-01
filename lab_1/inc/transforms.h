#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "common.h"
#include "stdio.h"
#include "errors.h"

typedef enum
{
    ROTATE,
    SHIFT,
    SCALE
} TransformType;

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

typedef struct 
{
    TransformType type;
    union 
    {
        TransformShift shift;
        TransformScale scale;
        TransformRotation rotation;
    };
} Transforms;

TransformShift TransformShiftInit(const double x, const double y, const double z);
TransformShift TransformShiftCreate(void);
TransformRotation TransformRotationCreate(void);
TransformScale TransformScaleCreate(void);
TransformModelData TransformModelDataCreate(void);

ErrorCode TransformModelDataUpdate(TransformModelData &transformModelData, const Transforms &transforms);

void TransformModelDataSetCenterShift(TransformModelData &transformModelData, const TransformShift &centerShift);

void TransoformsSetRotation(Transforms &transforms, const TransformRotation &rotation);
void TransoformsSetShift(Transforms &transforms, const TransformShift &shift);
void TransoformsSetScale(Transforms &transforms, const TransformScale &scale);
#endif