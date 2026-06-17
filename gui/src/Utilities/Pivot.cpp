#include "Utilities/UI/Pivot.h"

#include "Utilities/Math.h"

Pivot::Pivot(float x, float y)
{
    SetPivot(x, y);
}

void Pivot::SetPivot(float x, float y)
{
    SetXPivot(x);
    SetYPivot(y);
}

void Pivot::SetXPivot(float value)
{
    _x = Utilities::Math::Clamp(value, 0.f, 1.f);
}

void Pivot::SetYPivot(float value)
{
    _y = Utilities::Math::Clamp(value, 0.f, 1.f);
}

float Pivot::GetXPivot() const
{
    return _x;
}

float Pivot::GetYPivot() const
{
    return _y;
}
