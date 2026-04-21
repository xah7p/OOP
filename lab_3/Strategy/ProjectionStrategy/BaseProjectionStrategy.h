#pragma once

#include <memory>
#include "CarcassModelStructure.h"
#include "CameraEntityStructure.h"

class BaseProjectionStrategy {
public:
    BaseProjectionStrategy() = default;
    virtual ~BaseProjectionStrategy() = default;

    virtual void prepare(std::vector<Vertex>& projectedVertexes, 
        std::shared_ptr<CarcassModelStructure>,
        std::shared_ptr<CameraEntityStructure>) = 0;
};
