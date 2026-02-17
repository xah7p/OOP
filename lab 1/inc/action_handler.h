#ifndef DOMEN_H
#define DOMEN_H

#include "errors.h"
#include "window.h"
#include "model.h"

typedef enum
{
    MODEL_LOAD,
    MODEL_DRAW,
    MODEL_DESTROY,
    MODEL_ROTATE,
    MODEL_SCALE,
    MODEL_SHIFT
} ActionType;

typedef struct 
{
    const WindowContext &windowContext;
    ActionType type;
    TransformShift centerShift;
    union 
    {
        const char *filename;
        TransformShift shift;
        TransformScale scale;
        TransformRotation rotation;
    };
} Action; 

ErrorCode DomenHandleAction(Action &action);

#endif