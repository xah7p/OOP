#pragma once

#include "BaseEntity.h"
#include "LoadRequest.h"
#include "ReaderSolution.h"
#include "LoadDirectorSolution.h"

class LoadStrategy {
public:
    virtual ~LoadStrategy() = default;
    virtual std::shared_ptr<BaseEntity> load(
        const LoadRequest& req,
        std::shared_ptr<ReaderSolution> readerSolution,
        const std::shared_ptr<LoadDirectorSolution>& directorSolution) = 0;
};

class CarcassModelLoadStrategy: public LoadStrategy{
public:
    virtual ~CarcassModelLoadStrategy() override = default;
    virtual std::shared_ptr<BaseEntity> load(
        const LoadRequest& req,
        std::shared_ptr<ReaderSolution> readerSolution,
        const std::shared_ptr<LoadDirectorSolution>& directorSolution) override;
};

class CameraLoadStrategy: public LoadStrategy {
public:
    virtual ~CameraLoadStrategy() override = default;
    virtual std::shared_ptr<BaseEntity> load(
        const LoadRequest& req,
        std::shared_ptr<ReaderSolution> readerSolution,
        const std::shared_ptr<LoadDirectorSolution>& directorSolution) override;
};