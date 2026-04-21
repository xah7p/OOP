#include "Facade.h"

#include "ManagerFactory.h"
#include "ManagerPool.h"

Facade::Facade()
{
    auto factory = ManagerFactory::instance();
    factory->configureManagerPool();
    managerPool = std::make_unique<ManagerPoolReader>(ManagerPool::instance());
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    if (command)
        command->execute();
}
