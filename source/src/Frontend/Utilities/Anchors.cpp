#include "Frontend/Utilities/Anchors.h"

#include <utility>

#include "Frontend/Utilities/Math.h"

Anchors::Anchors(ImVec2&& min, ImVec2&& max)
{
    SetAnchors(std::move(min), std::move(max));
}

void Anchors::SetMinX(float minX)
{
    _min.x = Utilities::Math::Clamp(minX);
}

void Anchors::SetMinY(float minY)
{
    _min.y = Utilities::Math::Clamp(minY);
}

void Anchors::SetMaxX(float maxX)
{
    _max.x = Utilities::Math::Clamp(maxX);
}

void Anchors::SetMaxY(float maxY)
{
    _max.y = Utilities::Math::Clamp(maxY);
}

void Anchors::SetMin(ImVec2&& min)
{
    SetMinX(min.x);
    SetMinY(min.y);
}

void Anchors::SetMax(ImVec2&& max)
{
    SetMaxX(max.x);
    SetMaxY(max.y);
}

void Anchors::SetAnchors(ImVec2&& min, ImVec2&& max)
{
    SetMin(std::move(min));
    SetMax(std::move(max));
}

float Anchors::CalculatePositionLeft(float parentPositionLeft, float parentSizeX, float relativePositionX,
        float desiredSizeX, float pivotX) const
{
    float startPoint {CalculateStartPoint(parentPositionLeft, parentSizeX, _min.x)};

    float halfSize {CalculateSizeX(desiredSizeX, parentSizeX) / 2};

    float relativePoint {CalculateRelativePoint(relativePositionX, -halfSize * Utilities::Math::Absolute(_max.x - _min.x - 1))};

    relativePoint += halfSize + halfSize * -(pivotX * 2);

    return startPoint + relativePoint;
}

float Anchors::CalculatePositionTop(float parentPositionTop, float parentSizeY, float relativePositionY,
        float desiredSizeY, float pivotY) const
{
    float startPoint {CalculateStartPoint(parentPositionTop, parentSizeY, _min.y)};

    float halfSize {CalculateSizeY(desiredSizeY, parentSizeY) / 2};

    float relativePoint {CalculateRelativePoint(relativePositionY, -halfSize * Utilities::Math::Absolute(_max.y - _min.y - 1))};

    relativePoint += halfSize + halfSize * -(pivotY * 2);

    return startPoint + relativePoint;
}

float Anchors::CalculatePositionRight(float parentPositionRight, float parentSizeX, float relativePositionX,
        float desiredSizeX, float pivotX) const
{
    float startPoint {CalculateStartPoint(parentPositionRight, -parentSizeX, 1 - _max.x)};

    float halfSize {CalculateSizeX(desiredSizeX, parentSizeX) / 2};

    float relativePoint {CalculateRelativePoint(relativePositionX, halfSize * Utilities::Math::Absolute(_max.x - _min.x - 1))};

    relativePoint += halfSize + halfSize * -(pivotX * 2);

    return startPoint + relativePoint;
}

float Anchors::CalculatePositionBottom(float parentPositionBottom, float parentSizeY, float relativePositionY,
        float desiredSizeY, float pivotY) const
{
    float startPoint {CalculateStartPoint(parentPositionBottom, -parentSizeY, 1 - _max.y)};

    float halfSize {CalculateSizeY(desiredSizeY, parentSizeY) / 2};

    float relativePoint {CalculateRelativePoint(relativePositionY, halfSize * Utilities::Math::Absolute(_max.y - _min.y - 1))};

    relativePoint += halfSize + halfSize * -(pivotY * 2);

    return startPoint + relativePoint;
}

float Anchors::CalculateStartPoint(float parentPosition, float parentSize, float multiplier)
{
    return parentPosition + parentSize * multiplier;
}

float Anchors::CalculateRelativePoint(float relativePosition, float size)
{
    return relativePosition + size;
}

float Anchors::CalculateSizeX(float sizeX, float parentSizeX) const
{
    float multiplier {_max.x - _min.x};

    return sizeX * Utilities::Math::Absolute(multiplier - 1) + parentSizeX * multiplier;
}

float Anchors::CalculateSizeY(float sizeY, float parentSizeY) const
{
    float multiplier {_max.y - _min.y};

    return sizeY * Utilities::Math::Absolute(multiplier - 1) + parentSizeY * multiplier;
}