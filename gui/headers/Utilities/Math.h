#pragma once

namespace Utilities::Math
{
    template<typename T>
    [[nodiscard]] static T Absolute(T value);

    template<typename T>
    [[nodiscard]] static T Absolute(T value);

    template<typename T>
    [[nodiscard]] static T Min(T value, T min);

    template<typename T>
    [[nodiscard]] static T Max(T value, T max);

    template<typename T>
    [[nodiscard]] static T Clamp(T value, T min, T max);
}

template<typename T>
T Utilities::Math::Absolute(T value)
{
    if (value < 0.f)
    {
        value *= -1;
    }

    return value;
}

template<typename T>
T Utilities::Math::Min(T value, T min)
{
    if (value < min)
    {
        value = min;
    }

    return value;
}

template<typename T>
T Utilities::Math::Max(T value, T max)
{
    if (value > max)
    {
        value = max;
    }

    return value;
}

template<typename T>
T Utilities::Math::Clamp(T value, T min, T max)
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
