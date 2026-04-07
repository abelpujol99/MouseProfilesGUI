#pragma once
#include "imgui.h"

class IDrawRectangleStrategy
{
public:

    virtual ~IDrawRectangleStrategy() = default;

    virtual void DrawRectangle(ImDrawList* drawList, const ImVec2& position, const ImVec2& bottomRightPosition,
        const ImColor& color, float rounding, float thickness) = 0;
};
