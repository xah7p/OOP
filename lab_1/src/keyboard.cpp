#include "keyboard.h"

#define ROTATE_XLOW 's'
#define ROTATE_XUP  'w'
#define ROTATE_YLOW 'a'
#define ROTATE_YUP  'd'
#define ROTATE_ZLOW 'e'
#define ROTATE_ZUP  'q'

#define SCALE_LOW   'r'
#define SCALE_UP    't'

#define SHIFT_XLOW  'v'
#define SHIFT_XUP   'n'
#define SHIFT_YLOW  'g'
#define SHIFT_YUP   'b'

#define TRANSFORM_ROTATION_RATE 0.01
#define TRANSFORM_SHIFT_RATE 1
#define TRANSFORM_SCALE_RATE 1.001

bool CheckKeysForRotate(VAR TransformRotation &rotation, IN const WindowContext &windowContext)
{
    bool isAnyPressed = true;
    if (WindowContextCheckKeyPressed(windowContext, ROTATE_XLOW))
        rotation.x -= TRANSFORM_ROTATION_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, ROTATE_XUP))
        rotation.x += TRANSFORM_ROTATION_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, ROTATE_YLOW))
        rotation.y -= TRANSFORM_ROTATION_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, ROTATE_YUP))
        rotation.y += TRANSFORM_ROTATION_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, ROTATE_ZLOW))
        rotation.z -= TRANSFORM_ROTATION_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, ROTATE_ZUP))
        rotation.z += TRANSFORM_ROTATION_RATE;
    else
        isAnyPressed = false;
    return isAnyPressed;
}

bool CheckKeysForShift(VAR TransformShift &shift, IN const WindowContext &windowContext)
{
    bool isAnyPressed = true;
    if (WindowContextCheckKeyPressed(windowContext, SHIFT_XLOW))
        shift.x -= TRANSFORM_SHIFT_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, SHIFT_XUP))
        shift.x += TRANSFORM_SHIFT_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, SHIFT_YLOW))
        shift.y -= TRANSFORM_SHIFT_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, SHIFT_YUP))
        shift.y += TRANSFORM_SHIFT_RATE;
    else
        isAnyPressed = false;
    return isAnyPressed;
}

bool CheckKeysForScale(VAR TransformScale &scale, IN const WindowContext &windowContext)
{
    bool isAnyPressed = true;
    if (WindowContextCheckKeyPressed(windowContext, SCALE_LOW))
        scale.factor /= TRANSFORM_SCALE_RATE;
    else if (WindowContextCheckKeyPressed(windowContext, SCALE_UP))
        scale.factor *= TRANSFORM_SCALE_RATE;
    else
        isAnyPressed = false;
    return isAnyPressed;
}