#ifndef RGBA_H
#define RGBA_H

typedef struct 
{
    int r;
    int g;
    int b;
    int a;
} RGBA;

#define DEFAULT_COLOR_WHITE {255, 255, 255, 255}
#define DEFAULT_COLOR_BLACK {0, 0, 0, 255}

#endif