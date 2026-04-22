#pragma once 

#include "BaseManager.h"
#include <memory>

class ManagerCreator {
public:
    virtual ~ManagerCreator() = default;
    virtual std::shared_ptr<BaseManager> create() const = 0;
};

class DrawManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};

class TransformManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};

class HistoryManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};

class SceneManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};

class CameraManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};

class LoadManagerCreator: public ManagerCreator {
public:
    virtual std::shared_ptr<BaseManager> create() const override;
};