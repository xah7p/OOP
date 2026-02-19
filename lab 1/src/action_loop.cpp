#include "action_loop.h"
#include "actions.h"
#include "keyboard.h"

static ErrorCode HandleKeyboardInput(IN const WindowContext &WindowContext);

ErrorCode RunEventLoop(IN const WindowContext &windowContext, IN const char *filename, IN const int loopDelay)
{
    if (filename == NULL || loopDelay < 0)
        return INVALID_ARG;

    ErrorCode code = SUCCESS;
    code = ActionModelLoad(filename, windowContext);
    if (code == SUCCESS)
    {
        code = ActionModelDraw(windowContext);
        if (code == SUCCESS)
        {
            while (WindowContextLoop() == LOOP_RUNNING)
                if (WindowContextCheckKeyboard(windowContext))
                    HandleKeyboardInput(windowContext);
            WindowContextDelay(loopDelay);
        }
        ActionModelDestroy(windowContext);
    }
    return code;
}

static ErrorCode HandleKeyboardInput(IN const WindowContext &windowContext)
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