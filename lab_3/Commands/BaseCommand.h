#pragma once

#include <BaseManager.h>

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};