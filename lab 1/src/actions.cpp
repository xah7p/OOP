#include "errors.h"
#include "actions.h"

static TransformShift GetShiftCenter(IN const WindowContext &windowContext);

Action ActionCreate(IN const ActionType type, IN const WindowContext &windowContext)
{
    Action action = {.windowContext = windowContext, .type = type};
    return action;
}

ErrorCode ActionModelLoad(IN const char *filename, IN const WindowContext &windowContext)
{
    Action actionLoad = ActionCreate(MODEL_LOAD, windowContext);
    actionLoad.centerShift = GetShiftCenter(windowContext);
    actionLoad.filename = filename;
    
    return DomenHandleAction(actionLoad);
}

ErrorCode ActionModelDraw(IN const WindowContext &windowContext)
{
    Action actionDraw = ActionCreate(MODEL_DRAW, windowContext);
    return DomenHandleAction(actionDraw); 
}

void ActionModelDestroy(IN const WindowContext &windowContext)
{
    Action actionDestroy = ActionCreate(MODEL_DESTROY, windowContext);
    DomenHandleAction(actionDestroy);  
}

void ActionModelRotate(IN const TransformRotation &rotation, IN const WindowContext &windowContext)
{
    Action actionRotate = ActionCreate(MODEL_UPDATE, windowContext);
    TransoformsSetRotation(actionRotate.transforms, rotation);

    DomenHandleAction(actionRotate); 
}

void ActionModelShift(IN const TransformShift &shift, IN const WindowContext &windowContext)
{
    Action actionShift = ActionCreate(MODEL_UPDATE, windowContext);
    TransoformsSetShift(actionShift.transforms, shift);

    DomenHandleAction(actionShift); 
}

void ActionModelScale(IN const TransformScale &scale, IN const WindowContext &windowContext)
{
    Action actionScale = ActionCreate(MODEL_UPDATE, windowContext);
    TransoformsSetScale(actionScale.transforms, scale);

    DomenHandleAction(actionScale); 
}

static TransformShift GetShiftCenter(IN const WindowContext &windowContext)
{
    int width = 0, height = 0;
    WindowContextGetSizes(width, height, windowContext);
    TransformShift shiftCenter = TransformShiftCreate();
    shiftCenter.x = (double)width / 2;
    shiftCenter.y = (double)height / 2;
    return shiftCenter;
}