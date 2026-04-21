#include "LoadManager.h"

#include "ManagerPool.h"
#include "SceneManager.h"
#include "BaseManagerException.h"
#include "ModelException.h"

namespace
{
std::unique_ptr<BaseReaderCreator> createTxtModelReaderCreator() { return std::make_unique<TxtCarcassModelReaderCreator>(); }
std::unique_ptr<BaseReaderCreator> createObjModelReaderCreator() { return std::make_unique<ObjCarcassModelReaderCreator>(); }
std::unique_ptr<BaseReaderCreator> createBinModelReaderCreator() { return std::make_unique<BinCarcassModelReaderCreator>(); }
std::unique_ptr<BaseReaderCreator> createTxtCameraReaderCreator() { return std::make_unique<TxtDefaultCameraReaderCreator>(); }
std::unique_ptr<BaseReaderCreator> createObjCameraReaderCreator() { return std::make_unique<ObjDefaultCameraReaderCreator>(); }
std::unique_ptr<BaseReaderCreator> createBinCameraReaderCreator() { return std::make_unique<BinDefaultCameraReaderCreator>(); }

std::unique_ptr<BaseBuilderCreator> createListModelBuilderCreator() { return std::make_unique<ListCarcassModelBuilderCreator>(); }
std::unique_ptr<BaseBuilderCreator> createMatrixModelBuilderCreator() { return std::make_unique<MatrixCarcassModelBuilderCreator>(); }
std::unique_ptr<BaseBuilderCreator> createDefaultCameraBuilderCreator() { return std::make_unique<DefaultCameraBuilderCreator>(); }

std::unique_ptr<BaseDirectorCreator> createCarcassDirectorCreator() { return std::make_unique<CarcassDirectorCreator>(); }
std::unique_ptr<BaseDirectorCreator> createCameraDirectorCreator() { return std::make_unique<CameraDirectorCreator>(); }
}  

LoadManager::LoadManager()
{
    readerSolution = std::make_shared<ReaderSolution>();
    readerSolution->registrate("txt", EntityKind::Model, createTxtModelReaderCreator);
    readerSolution->registrate("obj", EntityKind::Model, createObjModelReaderCreator);
    readerSolution->registrate("bin", EntityKind::Model, createBinModelReaderCreator);
    readerSolution->registrate("csv", EntityKind::Model, createTxtModelReaderCreator);
    readerSolution->registrate("txt", EntityKind::Camera, createTxtCameraReaderCreator);
    readerSolution->registrate("obj", EntityKind::Camera, createObjCameraReaderCreator);
    readerSolution->registrate("bin", EntityKind::Camera, createBinCameraReaderCreator);

    builderSolution = std::make_shared<BuilderSolution>();
    builderSolution->registrate(EntityKind::Model, EntityStructureKind::ListCarcassModelStructure,
                                createListModelBuilderCreator);
    builderSolution->registrate(EntityKind::Model, EntityStructureKind::MatrixCarcassModelStructure,
                                createMatrixModelBuilderCreator);
    builderSolution->registrate(EntityKind::Camera, EntityStructureKind::DefaultCameraStructure,
                                createDefaultCameraBuilderCreator);

    directorSolution = std::make_shared<LoadDirectorSolution>();
    directorSolution->registrate(EntityKind::Model, createCarcassDirectorCreator);
    directorSolution->registrate(EntityKind::Camera, createCameraDirectorCreator);
}

void LoadManager::loadEntity(EntityId id, const LoadRequest& req)
{
    (void)id;
    auto readerCreator = readerSolution->create(req.path, req.kind);
    if (!readerCreator)
        throw ModelInvalidFileFormat("No reader creator for requested source/type.");

    auto reader = readerCreator->create(req.path);
    auto builderCreator = builderSolution->create(req.kind, req.structure);
    if (!builderCreator)
        throw BaseManagerException("No builder creator for requested entity/structure.");

    auto builder = builderCreator->create(std::shared_ptr<BaseReader>(std::move(reader)));
    auto directorCreator = directorSolution->create(req.kind);
    if (!directorCreator)
        throw BaseManagerException("No director creator for requested entity kind.");

    auto director = directorCreator->create(builder);
    auto entity = director->create();
    if (!entity)
        throw BaseManagerException("Director failed to create entity.");

    auto sceneManager = std::dynamic_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (sceneManager)
        (void)sceneManager->addEntity(entity);
    else
        throw BaseManagerException("SceneManager is not available in manager pool.");
}
