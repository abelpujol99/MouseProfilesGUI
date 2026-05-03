#include "Frontend/Utilities/Anchors.h"

#include "Frontend/Utilities/Math.h"

Anchors::Anchors(ImVec2 min, ImVec2 max)
{
    SetAnchors(min, max);
}

void Anchors::SetAnchors(ImVec2 min, ImVec2 max)
{
    SetHorizontalMinAnchor(min.x);
    SetHorizontalMaxAnchor(max.x);
    SetVerticalMinAnchor(min.y);
    SetVerticalMaxAnchor(max.y);
}

void Anchors::SetHorizontalAnchors(float min, float max)
{
    SetHorizontalMinAnchor(min);
    SetHorizontalMaxAnchor(max);
}

void Anchors::SetVerticalAnchors(float min, float max)
{
    SetVerticalMinAnchor(min);
    SetVerticalMaxAnchor(max);
}

void Anchors::SetHorizontalMinAnchor(float value)
{
    _min.x = Utilities::Math::Clamp(value, 0.f, 1.f);
}

void Anchors::SetHorizontalMaxAnchor(float value)
{
    _max.x = Utilities::Math::Clamp(value, 0.f, 1.f);
}

void Anchors::SetVerticalMinAnchor(float value)
{
    _min.y = Utilities::Math::Clamp(value, 0.f, 1.f);
}

void Anchors::SetVerticalMaxAnchor(float value)
{
    _max.y = Utilities::Math::Clamp(value, 0.f, 1.f);
}

float Anchors::GetHorizontalMinAnchor() const
{
    return _min.x;
}

float Anchors::GetHorizontalMaxAnchor() const
{
    return _max.x;
}

float Anchors::GetVerticalMinAnchor() const
{
    return _min.y;
}

float Anchors::GetVerticalMaxAnchor() const
{
    return _max.y;
}
