#include "action_loop.h"
#include "actions.h"
#include "keyboard.h"

static ErrorCode HandleKeyboardInput(const WindowContext &WindowContext);

ErrorCode RunEventLoop(const WindowContext &windowContext, const char *filename, const int loopDelay)
{
    ErrorCode code = SUCCESS;
    if (filename == NULL || loopDelay < 0)
        code = INVALID_ARG;
    else
    {
        code = ActionModelLoad(filename, windowContext);
        if (code == SUCCESS)
            code = ActionModelDraw(windowContext);
        
        while (code == SUCCESS && WindowContextLoop() == LOOP_RUNNING)
        {
            if (WindowContextCheckKeyboard(windowContext))
                HandleKeyboardInput(windowContext);
            WindowContextDelay(loopDelay);
        }
    }
    ActionModelDestroy(windowContext);
    return code;
}

static ErrorCode HandleKeyboardInput(const WindowContext &windowContext)
{
    ErrorCode code = SUCCESS;
    bool toRedraw = false;
    TransformRotation rotation = TransformRotationCreate();
    TransformScale scale = TransformScaleCreate();
    TransformShift shift = TransformShiftCreate();

    if (CheckKeysForRotate(rotation, windowContext))
    {
        ActionModelRotate(rotation, windowContext);
        toRedraw = true;
    }
    if (CheckKeysForShift(shift, windowContext))
    {
        ActionModelShift(shift, windowContext);
        toRedraw = true;
    }
    if (CheckKeysForScale(scale, windowContext))
    {
        ActionModelScale(scale, windowContext);
        toRedraw = true;
    }

    if (toRedraw)
        code = ActionModelDraw(windowContext);
    return code;
}