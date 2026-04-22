#ifndef MODEL_H
#define MODEL_H

#include "common.h"
#include "pointarr.h"
#include "linearr.h"

typedef struct 
{
    PointArr points;
    LineArr lines;
} Model;

Model ModelCreate(void);
void ModelFree(Model &model);
ErrorCode ModelLoad(Model &model, const char *filename);
ErrorCode ModelCopy(Model &dst, const Model &src);
ErrorCode ModelMove(Model &newModel, const Model &model);
void ModelTransform(Model &model, const TransformModelData &transformModelData);

#endif