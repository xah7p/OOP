#ifndef ACTIONS_H
#define ACTIONS_H

#include "errors.h"
#include "window.h"
#include "action_handler.h"

Action ActionCreate(const ActionType type, const WindowContext &windowContext);
ErrorCode ActionModelLoad(const char *filename, const WindowContext &windowContext);
ErrorCode ActionModelDraw(const WindowContext &windowContext);
void ActionModelDestroy(const WindowContext &windowContext);
void ActionModelRotate(const TransformRotation &rotation, const WindowContext &windowContext);
void ActionModelShift(const TransformShift &shift, const WindowContext &windowContext);
void ActionModelScale(const TransformScale &scale, const WindowContext &windowContext);

#endif