#pragma once

namespace Utilities::Math
{
    [[nodiscard]] static float Absolute(float value);

    [[nodiscard]] static int Absolute(int value);

    [[nodiscard]] static float Clamp(float value, float min, float max);
}

inline float Utilities::Math::Absolute(float value)
{
    if (value < 0.f)
    {
        value *= -1;
    }

    return value;
}

inline int Utilities::Math::Absolute(int value)
{
    if (value < 0)
    {
        value *= -1;
    }

    return value;
}

inline float Utilities::Math::Clamp(float value, float min, float max)
{
    if (value > max)
    {
        return max;
    }

    if (value < min)
    {
        return min;
    }

    return value;
}