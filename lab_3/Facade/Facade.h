#pragma once

#include "ManagerPoolReader.h"
#include "BaseCommand.h"
#include "BaseGraphicsScene.h"
#include "BasePainter.h"
#include <cstddef>
#include <memory>

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
    
    std::shared_ptr<BaseGraphicsScene> createGraphicsScene(size_t width, size_t height);
    std::shared_ptr<BasePainter> createPainter(const std::shared_ptr<BaseGraphicsScene>& scene);
};