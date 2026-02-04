#pragma once

enum class MouseButtons : char
{
    LEFT,
    RIGHT,
    MIDDLE,
    FOURTH,
    FIFTH,
    COUNT
};

inline MouseButtons& operator++(MouseButtons& gestureType)
{
    gestureType = static_cast<MouseButtons>(static_cast<char>(gestureType) + 1);

    return gestureType;
}