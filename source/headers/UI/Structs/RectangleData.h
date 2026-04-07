#pragma once
#include "imgui.h"

struct RectangleData
{
    const ImVec2& size;
    ImColor color;
    float rounding;
    float thickness;
    bool isFilled;
};
