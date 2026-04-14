#pragma once

namespace Utilities::Math
{
    [[nodiscard]] static float Absolute(float value);

    [[nodiscard]] static float Clamp(float value);
}

inline float Utilities::Math::Absolute(float value)
{
    if (value < 0.f)
    {
        value *= -1;
    }

    return value;
}

inline float Utilities::Math::Clamp(float value)
{
    if (value > 1.f)
    {
        return 1.f;
    }

    if (value < 0.f)
    {
        return 0.f;
    }

    return value;
}
