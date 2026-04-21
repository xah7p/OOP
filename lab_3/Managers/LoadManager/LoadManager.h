#pragma once

#include <map>
#include <memory>
#include "BaseManager.h"
#include "ReaderSolution.h"
#include "BuilderSolution.h"
#include "LoadDirectorSolution.h"
#include "LoadRequest.h"
#include "LoadStrategy.h"

class LoadManager: public BaseManager {
private:
    std::shared_ptr<ReaderSolution> readerSolution;
    std::shared_ptr<BuilderSolution> builderSolution;
    std::shared_ptr<LoadDirectorSolution> directorSolution;

    std::map<EntityKind, std::unique_ptr<LoadStrategy>> strategies;
public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void loadEntity(const LoadRequest& req);
};