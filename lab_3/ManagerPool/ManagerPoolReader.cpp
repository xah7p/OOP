#include "ManagerPoolReader.h"

ManagerPoolReader::ManagerPoolReader(std::shared_ptr<ManagerPool> managerPool):
    managerPool(std::move(managerPool))
{ }

std::shared_ptr<BaseManager> ManagerPoolReader::getManager(ManagerId id)
{
    return managerPool ? managerPool->getManager(id) : nullptr;
}
