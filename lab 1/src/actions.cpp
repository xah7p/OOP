#include "errors.h"
#include "actions.h"
#include "transforms.h"

static TransformShift GetShiftCenter(const WindowContext &windowContext);

Action ActionCreate(const ActionType type, const WindowContext &windowContext)
{
    Action action = {.windowContext = windowContext, .type = type};
    return action;
}

ErrorCode ActionModelLoad(const char *filename, const WindowContext &windowContext)
{
    Action actionLoad = ActionCreate(MODEL_LOAD, windowContext);
    actionLoad.centerShift = GetShiftCenter(windowContext);
    actionLoad.filename = filename;
    
    return DomenHandleAction(actionLoad);
}

ErrorCode ActionModelDraw(const WindowContext &windowContext)
{
    Action actionDraw = ActionCreate(MODEL_DRAW, windowContext);
    return DomenHandleAction(actionDraw); 
}

void ActionModelDestroy(const WindowContext &windowContext)
{
    Action actionDestroy = ActionCreate(MODEL_DESTROY, windowContext);
    DomenHandleAction(actionDestroy);  
}

void ActionModelRotate(const TransformRotation &rotation, const WindowContext &windowContext)
{
    Action actionRotate = ActionCreate(MODEL_ROTATE, windowContext);
    actionRotate.rotation = rotation;

    DomenHandleAction(actionRotate); 
}

void ActionModelShift(const TransformShift &shift, const WindowContext &windowContext)
{
    Action actionShift = ActionCreate(MODEL_SHIFT, windowContext);
    actionShift.shift = shift;

    DomenHandleAction(actionShift); 
}

void ActionModelScale(const TransformScale &scale, const WindowContext &windowContext)
{
    Action actionScale = ActionCreate(MODEL_SCALE, windowContext);
    actionScale.scale = scale;

    DomenHandleAction(actionScale); 
}

static TransformShift GetShiftCenter(const WindowContext &windowContext)
{
    int width = 0, height = 0;
    WindowContextGetSizes(windowContext, width, height);
    TransformShift shiftCenter = TransformShiftCreate();
    shiftCenter.x = (double)width / 2;
    shiftCenter.y = (double)height / 2;
    return shiftCenter;
}