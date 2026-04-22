#pragma once

#include <cstddef>

class Edge final {
private:
    size_t firstIndex;
    size_t secondIndex;
public:
    Edge() noexcept = default;
    Edge(size_t firstIndex, size_t secondIndex);

    explicit Edge(const Edge& other) noexcept = default;
    Edge(Edge&& other) noexcept = default;

    ~Edge() noexcept = default;

    Edge& operator=(const Edge& other) noexcept = default;
    Edge& operator=(Edge&& other) noexcept = default;

    size_t getFirst() const noexcept;
    size_t getSecond() const noexcept;

    void setFirst(size_t index) noexcept;
    void setSecond(size_t index) noexcept;
};