#include "model.h"
#include "file.h"
#include "point_arr_transform.h"

static ErrorCode ModelRead(VAR Model &model, IN FILE *f);
static ErrorCode ModelReadData(OUT Model &model, IN FILE *f);
static bool ModelCheckLinesValid(IN const Model &model);
static bool CheckLinesValid(IN const PointArr &points, IN const LineArr &lines);
static bool CheckLineValid(IN const Line &line, IN const size_t pointsCount);

Model ModelCreate(void)
{
    Model model = {PointArrCreate(), LineArrCreate()};
    return model;
}

void ModelFree(VAR Model &model)
{
    PointArrFree(model.points);
    LineArrFree(model.lines);
}

ErrorCode ModelLoad(VAR Model &model, IN const char *filename)
{
    if (!filename)
        return INVALID_ARG;
    
    ErrorCode code = SUCCESS;
    FILE *f = FileOpen(filename, READ);
    if (f == NULL)
        code = FILE_NOT_OPENED;
    else
    {
        code = ModelRead(model, f);
        FileClose(f);
    }
    return code;
}

ErrorCode ModelCopy(OUT Model &dst, IN const Model &src)
{
    ErrorCode code = SUCCESS;
    code = PointArrCopy(dst.points, src.points);

    if (code == SUCCESS)
        code = LineArrCopy(dst.lines, src.lines);

    return code;
}

void ModelTransform(OUT Model &model, IN const TransformModelData &transformModelData)
{
    PointArrRotateAroundCenter(model.points, transformModelData.rotation);
    PointArrScale(model.points, transformModelData.scale);
    PointArrShift(model.points, transformModelData.shift);
    PointArrShift(model.points, transformModelData.centerShift);
}

static ErrorCode ModelRead(VAR Model &model, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;
    
    ErrorCode code = SUCCESS;
    Model newModel = ModelCreate();
    code = ModelReadData(newModel, f);
    if (code == SUCCESS && ModelCheckLinesValid(newModel))
        model = newModel;
    else
    {
        ModelFree(newModel);
        code = INVALID_INPUT;
    }
    return code;
}

static ErrorCode ModelReadData(OUT Model &model, IN FILE *f)
{
    if (f == NULL)
        return INVALID_ARG;
    
    ErrorCode code = SUCCESS;
    code = PointArrRead(model.points, f);
    if (code == SUCCESS)
        code = LineArrRead(model.lines, f);
    
    return code;
}

static bool ModelCheckLinesValid(IN const Model &model)
{
    return CheckLinesValid(model.points, model.lines);
}

static bool CheckLinesValid(IN const PointArr &points, IN const LineArr &lines)
{
    bool isLinesValid = true;
    for (size_t i = 0; i < lines.size && isLinesValid; i++)
        if (!CheckLineValid(lines.inner[i], points.size))
            isLinesValid = false;
    return isLinesValid;
}

static bool CheckLineValid(IN const Line &line, IN const size_t pointsCount)
{
    return line.startIndex < pointsCount && line.endIndex < pointsCount;
}