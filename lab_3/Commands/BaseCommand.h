#pragma once

#include <memory>
#include <BaseManager.h>

class Command {
public:
    using ManagerPtr = std::shared_ptr<BaseManager>;
    using ManagerAction = void(ManagerPtr::*)();

    virtual ~Command() = default;
    virtual void execute(ManagerPtr, ManagerAction) = 0;
};