#include "draw.h"
#include "window_objects.h"

static WindowContextPoint WindowContextPointFromPoint(const Point &point);
static WindowContextLine WindowContextLineFromLine(const Line &Line, const Point *points);
static void LineArrDraw(const LineArr &lines, const PointArr &points, const WindowContext &windowContext);

ErrorCode ModelDraw(const Model &model, const TransformModelData &transformModelData, const WindowContext &windowContext)
{
    ErrorCode code = SUCCESS;
    
    Model newModel = ModelCreate();
    code = ModelCopy(newModel, model);
    if (code == SUCCESS)
    {
        ModelTransform(newModel, transformModelData);
        WindowContextClear(windowContext);
        LineArrDraw(newModel.lines, newModel.points, windowContext);
        WindowContextPresent(windowContext);
        ModelFree(newModel);
    }
    return code;
}

static WindowContextPoint WindowContextPointFromPoint(const Point &point)
{
    return WindowContextPointCreate(point.x, point.y);
}

static WindowContextLine WindowContextLineFromLine(const Line &line, const Point *points)
{
    WindowContextPoint start = WindowContextPointFromPoint(points[line.startIndex]);
    WindowContextPoint end = WindowContextPointFromPoint(points[line.endIndex]);

    return WindowContextLineCreate(start, end);
}

static void LineArrDraw(const LineArr &lines, const PointArr &points, const WindowContext &windowContext)
{
    for (size_t i = 0; i < lines.size; i++)
    {
        WindowContextLine ctxLine = WindowContextLineFromLine(lines.inner[i], points.inner);
        WindowContextDrawLine(windowContext, ctxLine.start, ctxLine.end);
    }
}
