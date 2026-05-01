#pragma once

#include "imgui.h"
#include "Math.h"

class Anchors
{
public:
    Anchors(ImVec2 min, ImVec2 max);

    void SetAnchors(ImVec2 min, ImVec2 max);

    void SetHorizontalAnchors(float min, float max);
    void SetVerticalAnchors(float min, float max);

    void SetHorizontalMinAnchor(float value);
    void SetHorizontalMaxAnchor(float value);
    void SetVerticalMinAnchor(float value);
    void SetVerticalMaxAnchor(float value);

    [[nodiscard]] float GetHorizontalMinAnchor() const;
    [[nodiscard]] float GetHorizontalMaxAnchor() const;
    [[nodiscard]] float GetVerticalMinAnchor() const;
    [[nodiscard]] float GetVerticalMaxAnchor() const;

//private:

    ImVec2 _min;
    ImVec2 _max;
};