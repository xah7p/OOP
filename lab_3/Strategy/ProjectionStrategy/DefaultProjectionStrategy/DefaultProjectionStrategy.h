#pragma once

#include "BaseProjectionStrategy.h"

class DefaultProjectionStrategy: public BaseProjectionStrategy {
public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    virtual void prepare(std::vector<Vertex>& projectedVertexes, 
        std::shared_ptr<CarcassModelStructure>,
        std::shared_ptr<CameraEntityStructure>) override;
};