#include "action_handler.h"
#include "draw.h"
#include "transforms.h"

ErrorCode DomenHandleAction(Action &action)
{
    ErrorCode code = SUCCESS;

    static Model model = ModelCreate();
    static TransformModelData transformModelData = TransformModelDataCreate();

    switch (action.type)
    {
    case MODEL_LOAD:
        TransformModelDataSetCenterShift(transformModelData, action.centerShift);
        code = ModelLoad(model, action.filename);
        break;
    case MODEL_DRAW:
        code = ModelDraw(model, transformModelData, action.windowContext);
        break;
    case MODEL_DESTROY:
        ModelFree(model);
        break;
    case MODEL_ROTATE:
        TransformModelDataAddRotation(transformModelData.rotation, action.rotation);
        break;
    case MODEL_SHIFT:
        TransformModelDataAddShift(transformModelData.shift, action.shift);
        break;
    case MODEL_SCALE:
        TransformModelDataAddScale(transformModelData.scale, action.scale);
        break;
    }
    return code;
}