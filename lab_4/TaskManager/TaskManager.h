#pragma once

#include "Task.h"
#include "../Defines.h"
#include <list>

class TaskManager {
private:
    std::list<Task> tasks_;

public:
    TaskManager() = default;
    ~TaskManager() = default;

    void addTask(const Task& task);
    bool removeTask() noexcept;

    void insertTaskByDirection(int floor, int currentFloor, Direction direction);
    int frontFloor() const noexcept;

    [[nodiscard]] bool hasTaskForFloor(int floor) const noexcept;
    [[nodiscard]] bool isEmpty() const noexcept;
};
