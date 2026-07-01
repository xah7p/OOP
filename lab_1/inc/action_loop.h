#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "common.h"
#include "errors.h"
#include "window.h"

ErrorCode RunEventLoop(const WindowContext &windowContext, const char *filename, const int loopDelay);

#endif