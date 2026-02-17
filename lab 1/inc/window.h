#ifndef WINDOW_H
#define WINDOW_H

#include <cstdio>
#include "rgba.h"
#include "window_objects.h"

typedef enum
{
    LOOP_RUNNING,
    LOOP_FINISHED
} LoopState;

typedef struct WindowContext WindowContext;

WindowContext *WindowContextCreate(const char *title, const size_t width, const size_t height);
void WindowContextDestroy(WindowContext **windowContext);

void WindowContextGetSizes(const WindowContext &windowContext, int &width, int &height);

void WindowContextPresent(const WindowContext &windowContext);
void WindowContextDelay(const int ms);
void WindowContextClear(const WindowContext &windowContext);

LoopState WindowContextLoop(void);

bool WindowContextCheckKeyboard(const WindowContext &windowContext);
bool WindowContextCheckKeyPressed(const WindowContext &windowContext, const char key);

void WindowContextSetPenColor(WindowContext &windowContext, const RGBA color);
void WindowContextSetBackgroundColor(WindowContext &windowContext, const RGBA color);
void WindowContextDrawLine(const WindowContext &windowContext, const WindowContextPoint &p1, const WindowContextPoint &p2);
#endif