#pragma once

#include "BaseSceneCommand.h"
#include "SceneManager.h"

class EntityDeleteCommand : public BaseSceneCommand {
private:
    EntityId id;
    std::shared_ptr<SceneManager> manager;
public:
    explicit EntityDeleteCommand(EntityId id);
    ~EntityDeleteCommand() override = default;

    void execute() override;
};
