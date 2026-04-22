#include "SceneClearCommand.h"

#include "ManagerPool.h"

SceneClearCommand::SceneClearCommand():
    method(&SceneManager::clear),
    manager(std::static_pointer_cast<SceneManager>(ManagerPool::instance()->getManager(ManagerIds::Scene)))
{ }

void SceneClearCommand::execute()
{
    if (manager)
        ((*manager).*method)();
}
