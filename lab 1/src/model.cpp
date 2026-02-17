#include "model.h"
#include "file.h"
#include "point_arr_transform.h"

static ErrorCode ModelRead(Model &model, FILE *f);
static bool CheckLinesValid(const PointArr &points, const LineArr &lines);
static bool CheckLineValid(const Line &line, const size_t pointsCount);

Model ModelCreate(void)
{
    Model model = {PointArrCreate(), LineArrCreate()};
    return model;
}

void ModelFree(Model &model)
{
    PointArrFree(model.points);
    LineArrFree(model.lines);
}

ErrorCode ModelLoad(Model &model, const char *filename)
{
    ErrorCode code = SUCCESS;
    if (!filename)
        code = INVALID_ARG;
    else
    {
        FILE *f = FileOpen(filename, READ);
        if (f == NULL)
            code = FILE_NOT_OPENED;
        else
        {
            code = ModelRead(model, f);
            FileClose(f);
        }
    }
    return code;
}

static ErrorCode ModelRead(Model &model, FILE *f)
{
    ErrorCode code = SUCCESS;

    if (f == NULL)
        return INVALID_ARG;

    code = PointArrRead(model.points, f);
    if (code != SUCCESS)
        PointArrFree(model.points);
    else
    {
        code = LineArrRead(model.lines, f);
        if (code != SUCCESS || !CheckLinesValid(model.points, model.lines))
        {
            PointArrFree(model.points);
            LineArrFree(model.lines);
        }
    }
    return code;
}

ErrorCode ModelCopy(Model &dst, const Model &src)
{
    ErrorCode code = SUCCESS;

    code = PointArrCopy(dst.points, src.points);

    if (code == SUCCESS)
        code = LineArrCopy(dst.lines, src.lines);

    return code;
}

void ModelTransform(Model &model, const TransformModelData &transformModelData)
{
    PointArrRotateAroundCenter(model.points, transformModelData.rotation);
    PointArrScale(model.points, transformModelData.scale);
    PointArrShift(model.points, transformModelData.shift);
    PointArrShift(model.points, transformModelData.centerShift);
}

static bool CheckLinesValid(const PointArr &points, const LineArr &lines)
{
    bool isLinesValid = true;
    for (size_t i = 0; i < lines.size && isLinesValid; i++)
        if (!CheckLineValid(lines.inner[i], points.size))
            isLinesValid = false;
    return isLinesValid;
}

static bool CheckLineValid(const Line &line, const size_t pointsCount)
{
    return line.startIndex < pointsCount && line.endIndex < pointsCount;
}