#pragma once

#include <memory>

#include "BaseBuilder.h"
#include "BaseReader.h"

class BaseBuilderCreator {
public:
    virtual ~BaseBuilderCreator() = default;
    virtual std::shared_ptr<BaseBuilder> create(const std::shared_ptr<BaseReader>& reader) const = 0;
};

class ListCarcassModelBuilderCreator: public BaseBuilderCreator {
public:
    std::shared_ptr<BaseBuilder> create(const std::shared_ptr<BaseReader>& reader) const override;
};

class MatrixCarcassModelBuilderCreator: public BaseBuilderCreator {
public:
    std::shared_ptr<BaseBuilder> create(const std::shared_ptr<BaseReader>& reader) const override;
};

class DefaultCameraBuilderCreator: public BaseBuilderCreator {
public:
    std::shared_ptr<BaseBuilder> create(const std::shared_ptr<BaseReader>& reader) const override;
};

class BuilderCreatorMaker {
public:
    template <typename TCreator>
    static std::unique_ptr<BaseBuilderCreator> createCreator()
    {
        return std::make_unique<TCreator>();
    }
};
