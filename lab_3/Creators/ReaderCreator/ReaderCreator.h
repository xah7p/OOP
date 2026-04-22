#pragma once

#include <memory>
#include <string>

#include "BaseReader.h"

class BaseReaderCreator {
public:
    virtual ~BaseReaderCreator() = default;
    virtual std::unique_ptr<BaseReader> create(const std::string& path) const = 0;
};

class TxtCarcassModelReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class ObjCarcassModelReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class BinCarcassModelReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class TxtDefaultCameraReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class ObjDefaultCameraReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class BinDefaultCameraReaderCreator: public BaseReaderCreator {
public:
    std::unique_ptr<BaseReader> create(const std::string& path) const override;
};

class ReaderCreatorMaker {
public:
    template <typename TCreator>
    static std::unique_ptr<BaseReaderCreator> createCreator()
    {
        return std::make_unique<TCreator>();
    }
};