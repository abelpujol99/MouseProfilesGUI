#pragma once

#include <functional>
#include <vector>
#include <memory>

class TriggerBus
{
    using TTrigger = std::function<void()>;
    
    using TTriggerVector = std::vector<std::shared_ptr<TTrigger>>;
    using TTriggerVectorIterator = typename TTriggerVector::iterator;
    using TTriggerVectorConstIterator = typename TTriggerVector::const_iterator;
    
public:
    
    TriggerBus() = default;
    ~TriggerBus() noexcept;

    void Trigger();
    
    std::weak_ptr<TTrigger> Subscribe(TTrigger&& action);
    void Unsubscribe(std::weak_ptr<TTrigger>&& weakAction);
    void UnsubscribeAll();

private:

    TTriggerVector _triggers;

};