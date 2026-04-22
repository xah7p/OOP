#pragma once

#include <memory>
#include <vector>
#include "Scene.h"
#include "BaseManager.h"
#include "BaseEntity.h"
#include "EntityId.h"

class SceneManager: public BaseManager {
private:
    std::shared_ptr<Scene> scene;
public:
    SceneManager();
    virtual ~SceneManager() override = default;

    std::shared_ptr<Scene> getScene();
    void setScene(std::shared_ptr<Scene>);

    std::shared_ptr<BaseEntity> getEntity(EntityId id);
    [[nodiscard]] bool addEntity(std::shared_ptr<BaseEntity>);
    [[nodiscard]] bool removeEntity(EntityId id);
    bool createComposite(const std::vector<EntityId>& ids);

    void clear();
};