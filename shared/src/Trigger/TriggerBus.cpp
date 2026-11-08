#include "Trigger/TriggerBus.h"

TriggerBus::~TriggerBus() noexcept
{
    UnsubscribeAll();
}

void TriggerBus::Trigger()
{
    TTriggerVectorConstIterator itEnd {_triggers.cend()};

    for (TTriggerVectorIterator it {_triggers.begin()}; it != itEnd; ++it)
    {
        (**it)();
    }
}

std::weak_ptr<TriggerBus::TTrigger> TriggerBus::Subscribe(std::function<void()>&& action)
{
    std::shared_ptr<TTrigger> sharedAction {std::make_shared<TTrigger>(action)};
    _triggers.emplace_back(sharedAction);
    return sharedAction;
}

void TriggerBus::Unsubscribe(std::weak_ptr<TTrigger>&& weakAction)
{
    if (const auto action {weakAction.lock()})
    {
        TTriggerVectorConstIterator itEnd {_triggers.cend()};

        for (TTriggerVectorIterator it {_triggers.begin()}; it != itEnd; ++it)
        {
            if (*it != action)
            {
                continue;
            }

            _triggers.erase(it);

            return;
        }
    }
}

void TriggerBus::UnsubscribeAll()
{
    _triggers.clear();
}