#include "DrawCommand.h"
#include "ManagerPool.h"

DrawCommand::DrawCommand():
    method(&DrawManager::draw),
    manager(std::static_pointer_cast<DrawManager>(ManagerPool::instance()->getManager(ManagerIds::Draw)))
{ }

void DrawCommand::execute()
{
    if (manager)
        ((*manager).*method)();
}
