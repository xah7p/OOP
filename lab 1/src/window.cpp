#include "window.h"
#include "rgba.h"
#include <SDL2/SDL.h>

struct WindowContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    RGBA penColor;
    RGBA backgroundColor;
    const Uint8 *keyboardState;
};

WindowContext *WindowContextCreate(const char *title, const size_t width, const size_t height)
{
    if (!title)
        return NULL;

    WindowContext *windowContext = (WindowContext *)malloc(sizeof(WindowContext));
    if (windowContext)
    {
        SDL_InitSubSystem(SDL_INIT_VIDEO);
        windowContext->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                width, height, SDL_WINDOW_SHOWN);
        if (windowContext->window)
            windowContext->renderer = SDL_CreateRenderer(windowContext->window, -1, SDL_RENDERER_ACCELERATED);
    }

    if (windowContext && (!windowContext->window || !windowContext->renderer))
    {
        if (windowContext->window)
            SDL_DestroyWindow(windowContext->window);
        free(windowContext);
        windowContext = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    
    if (windowContext)
    {
        WindowContextSetPenColor(*windowContext, DEFAULT_COLOR_BLACK);
        WindowContextSetBackgroundColor(*windowContext, DEFAULT_COLOR_WHITE);
        windowContext->keyboardState = SDL_GetKeyboardState(NULL);
    }
    return windowContext;
}

void WindowContextSetPenColor(WindowContext &windowContext, const RGBA color)
{
    windowContext.penColor = color;
    SDL_SetRenderDrawColor(windowContext.renderer, color.r, color.g, color.b, color.a);
}

void WindowContextSetBackgroundColor(WindowContext &windowContext, const RGBA color)
{
    windowContext.backgroundColor = color;
}

void WindowContextDestroy(WindowContext **windowContext)
{
    if (windowContext && *windowContext)
    {
        SDL_DestroyWindow((*windowContext)->window);
        SDL_DestroyRenderer((*windowContext)->renderer);
        free(*windowContext);
        *windowContext = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
}

void WindowContextPresent(const WindowContext &windowContext)
{
    SDL_RenderPresent(windowContext.renderer);
}

void WindowContextDelay(const int ms)
{
    SDL_Delay(ms);
}

void WindowContextClear(const WindowContext &windowContext)
{
    const RGBA backgroundColor = windowContext.backgroundColor;
    const RGBA penColor = windowContext.penColor;

    SDL_SetRenderDrawColor(windowContext.renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(windowContext.renderer);
    SDL_SetRenderDrawColor(windowContext.renderer, penColor.r, penColor.g, penColor.b, penColor.a);
}

LoopState WindowContextLoop(void)
{
    static LoopState loopState = LOOP_RUNNING;
    static SDL_Event event;

    while (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT)
            loopState = LOOP_FINISHED;
    return loopState;
}

bool WindowContextCheckKeyboard(const WindowContext &windowContext)
{
    bool isSomethingPressed = false;
    for (size_t i = 0; i < SDL_NUM_SCANCODES && isSomethingPressed == false; i++)
        if (windowContext.keyboardState[i])
            isSomethingPressed = true;
    return isSomethingPressed;
}

bool WindowContextCheckKeyPressed(const WindowContext &windowContext, const char key)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(tolower(key));
    return windowContext.keyboardState[scancode];
}

void WindowContextDrawLine(const WindowContext &windowContext, const WindowContextPoint &p1, const WindowContextPoint &p2)
{
    SDL_RenderDrawLine(windowContext.renderer, p1.x, p1.y, p2.x, p2.y);
}

void WindowContextGetSizes(const WindowContext &windowContext, int &width, int &height)
{
    SDL_GetWindowSize(windowContext.window, &width, &height);
}