#include "draw.h"
#include "window_objects.h"

static void ModelObjectsDraw(IN const Model &newModel, IN const WindowContext &windowContext);
static WindowContextPoint WindowContextPointFromPoint(IN const Point &point);
static WindowContextLine WindowContextLineFromLine(IN const Line &Line, IN const Point *points);
static void LineArrDraw(IN const LineArr &lines, IN const PointArr &points, IN const WindowContext &windowContext);

ErrorCode ModelDraw(IN const Model &model, IN const TransformModelData &transformModelData, IN const WindowContext &windowContext)
{
    ErrorCode code = SUCCESS;
    
    Model newModel = ModelCreate();
    code = ModelCopy(newModel, model);
    if (code == SUCCESS)
    {
        ModelTransform(newModel, transformModelData);
        WindowContextClear(windowContext);
        ModelObjectsDraw(newModel, windowContext);
        WindowContextPresent(windowContext);
        ModelFree(newModel);
    }
    return code;
}

static void ModelObjectsDraw(IN const Model &newModel, IN const WindowContext &windowContext)
{
    LineArrDraw(newModel.lines, newModel.points, windowContext);
}

static WindowContextPoint WindowContextPointFromPoint(IN const Point &point)
{
    return WindowContextPointCreate(point.x, point.y);
}

static WindowContextLine WindowContextLineFromLine(IN const Line &line, IN const Point *points)
{
    WindowContextPoint start = WindowContextPointFromPoint(points[line.startIndex]);
    WindowContextPoint end = WindowContextPointFromPoint(points[line.endIndex]);

    return WindowContextLineCreate(start, end);
}

static void LineArrDraw(IN const LineArr &lines, IN const PointArr &points, IN const WindowContext &windowContext)
{
    for (size_t i = 0; i < lines.size; i++)
    {
        WindowContextLine ctxLine = WindowContextLineFromLine(lines.inner[i], points.inner);
        WindowContextDrawLine(windowContext, ctxLine.start, ctxLine.end);
    }
}
