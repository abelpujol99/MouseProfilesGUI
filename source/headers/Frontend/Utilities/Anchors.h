#pragma once

#include "imgui.h"

class Anchors
{
public:

    Anchors() = default;
    Anchors(ImVec2&& min, ImVec2&& max);

    ~Anchors() = default;

    void SetMinX(float minX);
    void SetMinY(float minY);
    void SetMaxX(float maxX);
    void SetMaxY(float maxY);

    void SetMin(ImVec2&& min);
    void SetMax(ImVec2&& max);

    void SetAnchors(ImVec2&& min, ImVec2&& max);

    [[nodiscard]] float CalculatePositionLeft(float parentPositionLeft, float parentSizeX, float relativePositionX,
        float desiredSizeX, float pivotX) const;

    [[nodiscard]] float CalculatePositionTop(float parentPositionTop, float parentSizeY, float relativePositionY,
        float desiredSizeY, float pivotY) const;

    [[nodiscard]] float CalculatePositionRight(float parentPositionRight, float parentSizeX, float relativePositionX,
        float desiredSizeX, float pivotX) const;

    [[nodiscard]] float CalculatePositionBottom(float parentPositionBottom, float parentSizeY, float relativePositionY,
        float desiredSizeY, float pivotY) const;

private:

    static float CalculateStartPoint(float parentPosition, float parentSize, float multiplier);

    static float CalculateRelativePoint(float relativePosition, float size);

    float CalculateSizeX(float desiredSizeX, float parentSizeX) const;

    float CalculateSizeY(float desiredSizeY, float parentSizeY) const;

    ImVec2 _min;
    ImVec2 _max;
};
