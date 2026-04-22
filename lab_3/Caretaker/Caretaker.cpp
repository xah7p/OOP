#include "Caretaker.h"

void Caretaker::set(EntityId id, unique_ptr<Memento> memento)
{
    if (!memento)
        return;

    mementos.emplace_back(id, std::move(memento));
    while (mementos.size() > 20)
        mementos.pop_front();
}

unique_ptr<Memento> Caretaker::get(EntityId id)
{
    for (auto it = mementos.rbegin(); it != mementos.rend(); ++it)
    {
        if (it->first == id)
        {
            auto memento = std::move(it->second);
            mementos.erase(std::next(it).base());
            return memento;
        }
    }
    return nullptr;
}
