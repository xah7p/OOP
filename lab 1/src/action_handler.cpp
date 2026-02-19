#include "action_handler.h"
#include "draw.h"
#include "transforms.h"

ErrorCode DomenHandleAction(IN const Action &action)
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
    case MODEL_UPDATE:
        code = TransformModelDataUpdate(transformModelData, action.transforms);
        break;
    case MODEL_DESTROY:
        ModelFree(model);
        break;
    }
    return code;
}