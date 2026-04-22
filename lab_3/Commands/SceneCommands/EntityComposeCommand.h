#pragma once

#include "BaseSceneCommand.h"
#include "SceneManager.h"
#include <vector>

class EntityComposeCommand : public BaseSceneCommand {
private:
    std::vector<EntityId> ids;
    bool& result;
    std::shared_ptr<SceneManager> manager;
public:
    EntityComposeCommand(std::vector<EntityId> ids, bool& result);
    ~EntityComposeCommand() override = default;

    void execute() override;
};
