#include "TaskManager.h"
#include <algorithm>

void TaskManager::addTask(const Task& task) {
    if (hasTaskForFloor(task.getFloor()))
        return;
    tasks_.push_front(task);
}

bool TaskManager::removeTask() noexcept {
    if (tasks_.empty())
        return false;
    tasks_.pop_front();
    return true;
}

void TaskManager::insertTaskByDirection(int floor, int currentFloor, Direction direction) {
    if (hasTaskForFloor(floor))
        return;

    Task target(floor);
    auto it = tasks_.begin();

    while (it != tasks_.end() && (it->getFloor() - currentFloor) * direction > 0) {
        if ((currentFloor - floor) * (floor - it->getFloor()) > 0) {
            tasks_.insert(it, target);
            return;
        }
        ++it;
    }

    if ((floor - currentFloor) * direction > 0) {
        tasks_.insert(it, target);
        return;
    }

    while (it != tasks_.end()) {
        if ((floor - it->getFloor()) * direction > 0) {
            tasks_.insert(it, target);
            return;
        }
        ++it;
    }

    tasks_.push_back(target);
}

int TaskManager::frontFloor() const noexcept {
    if (tasks_.empty())
        return NO_TARGET;
    return tasks_.front().getFloor();
}

bool TaskManager::hasTaskForFloor(int floor) const noexcept {
    auto iterator = std::find_if(tasks_.begin(), tasks_.end(), [floor](const Task& task) {
        return task.getFloor() == floor;
    });
    return iterator != tasks_.end();
}

bool TaskManager::isEmpty() const noexcept {
    return tasks_.empty();
}
