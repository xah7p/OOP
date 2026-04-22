#pragma once

#include "BaseManagerFactory.h"
#include "ManagerSolution.h"
#include <memory>

class ManagerFactory: public BaseManagerFactory {
private:
    std::unique_ptr<ManagerSolution> solution;
    ManagerFactory();
public:
    static std::shared_ptr<BaseManagerFactory> instance() {
        class Proxy: public ManagerFactory {};
        static std::shared_ptr<BaseManagerFactory> myInstance = std::make_shared<Proxy>();
        return myInstance;
    }
    virtual ~ManagerFactory() override = default;
    virtual void configureManagerPool() override;
};