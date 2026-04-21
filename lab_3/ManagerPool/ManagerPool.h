#pragma once

#include "BaseManager.h"
#include "ManagerId.h"
#include <map>
#include <memory>

class ManagerPool {
private:
    std::map<ManagerId, std::shared_ptr<BaseManager>> managers;
    ManagerPool();
public:
    static std::shared_ptr<ManagerPool> instance() {
        class Proxy: public ManagerPool {};
        static std::shared_ptr<ManagerPool> myInstance = std::make_shared<Proxy>();
        return myInstance;
    }
    ~ManagerPool() = default;
    std::shared_ptr<BaseManager> getManager(ManagerId id);
    bool registerManager(ManagerId id, std::shared_ptr<BaseManager> manager);
    bool unregisterManager(ManagerId id);
};