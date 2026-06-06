#pragma once

enum EventType : char
{
    REQUEST_DEVICES,
    COUNT
};

inline EventType& operator++(EventType& eventType)
{
    eventType = static_cast<EventType>(static_cast<char>(eventType) + 1);

    return eventType;
}