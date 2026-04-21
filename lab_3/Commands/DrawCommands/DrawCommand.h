#pragma once 

#include "BaseDrawCommand.h"
#include "DrawManager.h"

class DrawCommand: public BaseDrawCommand {
private:
    using ManagerMethod = void (DrawManager::*)();

    ManagerMethod method;
    std::shared_ptr<DrawManager> manager;
public:
    DrawCommand() = default;
    virtual ~DrawCommand() override = default;

    void execute() override;
};
