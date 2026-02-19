#ifndef DRAW_H
#define DRAW_H

#include "common.h"
#include "errors.h"
#include "model.h"
#include "window.h"
#include "transforms.h"

ErrorCode ModelDraw(const Model &model, const TransformModelData &transformModelData, const WindowContext &windowContext);

#endif