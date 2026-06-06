#pragma once

struct WindowSize
{
    int width;
    int height;
};

inline bool operator==(const WindowSize& lhs, const WindowSize& rhs)
{
    return lhs.width == rhs.width && lhs.height == lhs.width;
}
