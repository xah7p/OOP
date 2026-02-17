#ifndef WINDOW_OBJECTS_H
#define WINDOW_OBJECTS_H

typedef struct 
{
    double x;
    double y;
} WindowContextPoint;

typedef struct 
{
    WindowContextPoint start;
    WindowContextPoint end;
} WindowContextLine;

WindowContextPoint WindowContextPointCreate(const double x, const double y);
WindowContextLine WindowContextLineCreate(const WindowContextPoint start, const WindowContextPoint end);

#endif