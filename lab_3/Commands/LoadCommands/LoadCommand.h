#pragma once 

#include "BaseLoadCommand.h"
#include "LoadManager.h"
#include "LoadRequest.h"

class LoadCommand: public BaseLoadCommand {
private:
    using ManagerMethod = void (LoadManager::*)(const LoadRequest&);

    LoadRequest req;
    ManagerMethod method;
    std::shared_ptr<LoadManager> manager;
public:
    LoadCommand(const LoadRequest& req);
    virtual ~LoadCommand() override = default;

    void execute() override;
};
