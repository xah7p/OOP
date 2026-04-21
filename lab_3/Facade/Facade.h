#pragma once

#include "ManagerPoolReader.h"
#include "BaseCommand.h"

class Facade {
private:
    std::unique_ptr<ManagerPoolReader> managerPool;
    Facade();
public:
    static std::shared_ptr<Facade> instance() {
        class Proxy: public Facade {};
        static std::shared_ptr<Facade> myInstance = std::make_shared<Proxy>();
        return myInstance;
    }
    void execute(std::shared_ptr<BaseCommand> command);
};