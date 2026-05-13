#include "Task.h"

Task::Task(int floor)
    : floor_(floor) {}

int Task::getFloor() const noexcept {
    return floor_;
}

void Task::setFloor(int floor) noexcept {
    floor_ = floor;
}

[[nodiscard]] bool Task::operator==(const Task& other) const noexcept {
    return floor_ == other.floor_;
}

[[nodiscard]] bool Task::operator!=(const Task& other) const noexcept {
    return floor_ != other.floor_;
}
