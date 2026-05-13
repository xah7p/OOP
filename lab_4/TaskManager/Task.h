#pragma once

class Task {
private:
    int floor_;

public:
    explicit Task(int floor);
    ~Task() = default;

    int getFloor() const noexcept;
    void setFloor(int floor) noexcept;

    [[nodiscard]] bool operator==(const Task& other) const noexcept;
    [[nodiscard]] bool operator!=(const Task& other) const noexcept;
};
