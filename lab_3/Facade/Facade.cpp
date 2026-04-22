#include "Facade.h"

#include "ManagerFactory.h"
#include "ManagerPool.h"
#include "DrawManager.h"
#include "DrawFactoryCreator.h"
#include "QtDrawFactory.h"

Facade::Facade()
{
    auto factory = ManagerFactory::instance();
    factory->configureManagerPool();
    managerPool = std::make_unique<ManagerPoolReader>(ManagerPool::instance());
}

std::shared_ptr<BaseGraphicsScene> Facade::createGraphicsScene(size_t width, size_t height)
{
    auto drawFactory = DrawFactoryCreator::create<QtDrawFactory>();
    return drawFactory ? drawFactory->createGraphicsScene(width, height) : nullptr;
}

std::shared_ptr<BasePainter> Facade::createPainter(const std::shared_ptr<BaseGraphicsScene>& scene)
{
    if (!scene)
        return nullptr;
    auto drawFactory = DrawFactoryCreator::create<QtDrawFactory>();
    if (!drawFactory)
        return nullptr;
    auto painter = drawFactory->createPainter(scene);
    auto drawManager = std::static_pointer_cast<DrawManager>(
        ManagerPool::instance()->getManager(ManagerIds::Draw));
    if (drawManager)
        drawManager->setPainter(painter);
    return painter;
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    if (command)
        command->execute();
}
