#include "LoadManager.h"

#include "ManagerPool.h"
#include "SceneManager.h"
#include "BaseManagerException.h"
#include "ModelException.h"

LoadManager::LoadManager()
{
    readerSolution = std::make_shared<ReaderSolution>();
    readerSolution->registrate("txt", EntityKind::Model,
        ReaderCreatorMaker::createCreator<TxtCarcassModelReaderCreator>);
    readerSolution->registrate("obj", EntityKind::Model,
        ReaderCreatorMaker::createCreator<ObjCarcassModelReaderCreator>);
    readerSolution->registrate("bin", EntityKind::Model,
        ReaderCreatorMaker::createCreator<BinCarcassModelReaderCreator>);
    readerSolution->registrate("csv", EntityKind::Model,
        ReaderCreatorMaker::createCreator<TxtCarcassModelReaderCreator>);
    readerSolution->registrate("txt", EntityKind::Camera,
        ReaderCreatorMaker::createCreator<TxtDefaultCameraReaderCreator>);
    readerSolution->registrate("obj", EntityKind::Camera,
        ReaderCreatorMaker::createCreator<ObjDefaultCameraReaderCreator>);
    readerSolution->registrate("bin", EntityKind::Camera,
        ReaderCreatorMaker::createCreator<BinDefaultCameraReaderCreator>);

    builderSolution = std::make_shared<BuilderSolution>();
    builderSolution->registrate(EntityKind::Model, EntityStructureKind::ListCarcassModelStructure,
        BuilderCreatorMaker::createCreator<ListCarcassModelBuilderCreator>);
    builderSolution->registrate(EntityKind::Model, EntityStructureKind::MatrixCarcassModelStructure,
        BuilderCreatorMaker::createCreator<MatrixCarcassModelBuilderCreator>);
    builderSolution->registrate(EntityKind::Camera, EntityStructureKind::DefaultCameraStructure,
        BuilderCreatorMaker::createCreator<DefaultCameraBuilderCreator>);

    directorSolution = std::make_shared<LoadDirectorSolution>();
    directorSolution->registrate(EntityKind::Model,
        DirectorCreatorMaker::createCreator<CarcassDirectorCreator>);
    directorSolution->registrate(EntityKind::Camera,
        DirectorCreatorMaker::createCreator<CameraDirectorCreator>);
}

void LoadManager::loadEntity(EntityId id, const LoadRequest& req)
{
    (void)id;
    auto readerCreator = readerSolution->create(req.path, req.kind);
    if (!readerCreator)
        throw ModelInvalidFileFormat("No reader creator for requested source/type.");

    std::shared_ptr<BaseReader> reader = readerCreator->create(req.path);
    auto directorCreator = directorSolution->create(req.kind);
    if (!directorCreator)
        throw BaseManagerException("No director creator for requested entity kind.");

    auto director = directorCreator->create(reader, req.structure, builderSolution);
    auto entity = director->create();
    if (!entity)
        throw BaseManagerException("Director failed to create entity.");

    auto sceneManager = std::static_pointer_cast<SceneManager>(
        ManagerPool::instance()->getManager(ManagerIds::Scene));
    if (sceneManager)
        (void)sceneManager->addEntity(entity);
    else
        throw BaseManagerException("SceneManager is not available in manager pool.");
}
