#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "transforms.h"
#include "window.h"

bool CheckKeysForRotate(TransformRotation &rotation, const WindowContext &windowContext);
bool CheckKeysForShift(TransformShift &shift, const WindowContext &windowContex);
bool CheckKeysForScale(TransformScale &scale, const WindowContext &windowContex);

#endif