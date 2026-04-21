#pragma once

#include "BaseEntity.h"
#include "EntityId.h"
#include <memory>

class Scene {
private:
    BaseEntityMap entities;  
    size_t size = 0;
    Scene() = default;
public:
    using value_type = BaseEntityPtr;
    using size_type = size_t;
    using iterator = BaseEntityMap::iterator;
    using const_iterator = BaseEntityMap::const_iterator;

    static std::shared_ptr<Scene> instance() {
        class Proxy: public Scene {};
        static std::shared_ptr<Scene> myInstance = std::make_shared<Proxy>();
        return myInstance;
    }

    Scene(const Scene& other) = delete;
    Scene(Scene&& other) = delete;

    Scene& operator=(const Scene& other) = delete;
    Scene& operator=(Scene&& other) = delete;

    ~Scene() = default;

    [[nodiscard]] bool addEntity(std::shared_ptr<BaseEntity>);
    [[nodiscard]] bool removeEntity(EntityId id);
    std::shared_ptr<BaseEntity> getEntity(EntityId id);

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    void accept(std::shared_ptr<BaseVisitor>);
    void clear();
};