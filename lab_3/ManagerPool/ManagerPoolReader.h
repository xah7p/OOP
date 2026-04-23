#pragma once

#include "ManagerPool.h"

class ManagerPoolReader {
private:
    std::shared_ptr<ManagerPool> managerPool;
public:
    ManagerPoolReader(std::shared_ptr<ManagerPool> managerPool);
    std::shared_ptr<BaseManager> getManager(ManagerId id); 
};