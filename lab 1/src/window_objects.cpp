#include "window_objects.h"

WindowContextPoint WindowContextPointCreate(const double x, const double y)
{
    WindowContextPoint point;
    point.x = x;
    point.y = y;
    return point;
}

WindowContextLine WindowContextLineCreate(const WindowContextPoint start, const WindowContextPoint end)
{
    WindowContextLine line;
    line.start = start;
    line.end = end;
    return line;
}