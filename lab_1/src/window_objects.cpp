#include "window_objects.h"

WindowContextPoint WindowContextPointCreate(IN const double x, IN const double y)
{
    WindowContextPoint point;
    point.x = x;
    point.y = y;
    return point;
}

WindowContextLine WindowContextLineCreate(IN const WindowContextPoint start, IN const WindowContextPoint end)
{
    WindowContextLine line;
    line.start = start;
    line.end = end;
    return line;
}