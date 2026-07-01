#ifndef DOMEN_H
#define DOMEN_H

#include "common.h"
#include "errors.h"
#include "window.h"
#include "model.h"

typedef enum
{
    MODEL_LOAD,
    MODEL_DRAW,
    MODEL_DESTROY,
    MODEL_UPDATE
} ActionType;

typedef struct 
{
    const WindowContext &windowContext;
    ActionType type;
    const char *filename;
    TransformShift centerShift;
    Transforms transforms;
} Action; 

ErrorCode DomenHandleAction(const Action &action);

#endif