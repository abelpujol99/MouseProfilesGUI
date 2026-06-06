#pragma once

class IEventBus
{
public:

    virtual ~IEventBus() = default;

    virtual void UnsubscribeAll() = 0;
};