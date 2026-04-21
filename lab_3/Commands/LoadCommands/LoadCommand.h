#pragma once 

#include "BaseLoadCommand.h"
#include "LoadManager.h"
#include "LoadRequest.h"
#include "EntityId.h"

class LoadCommand: public BaseLoadCommand {
private:
    using ManagerMethod = void (LoadManager::*)(EntityId, const LoadRequest&);

    EntityId entityId;
    LoadRequest req;
    ManagerMethod method;
    std::shared_ptr<LoadManager> manager;
public:
    LoadCommand(EntityId id, const LoadRequest& req);
    virtual ~LoadCommand() override = default;

    void execute() override;
};
