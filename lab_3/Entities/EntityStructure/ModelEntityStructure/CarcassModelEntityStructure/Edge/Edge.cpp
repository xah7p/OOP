#include "Edge.h"

Edge::Edge(size_t firstIndex, size_t secondIndex):
    firstIndex(firstIndex), secondIndex(secondIndex)
{ }

size_t Edge::getFirst() const noexcept
{
    return firstIndex;
}

size_t Edge::getSecond() const noexcept
{
    return secondIndex;
}

void Edge::setFirst(size_t index) noexcept
{
    firstIndex = index;
}

void Edge::setSecond(size_t index) noexcept
{
    secondIndex = index;
}
