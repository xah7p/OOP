#pragma once 

#include "BaseSceneCommand.h"
#include "SceneManager.h"

class SceneClearCommand: public BaseSceneCommand {
private:
    using ManagerMethod = void (SceneManager::*)();

    ManagerMethod method;
    std::shared_ptr<SceneManager> manager;
public:
    SceneClearCommand();
    virtual ~SceneClearCommand() override = default;

    void execute() override;
};
