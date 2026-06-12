#pragma once

#include "IDrawRectangleStrategy.h"

class DrawEmptyRectangle : public IDrawRectangleStrategy
{
public:

    ~DrawEmptyRectangle() override = default;

    void DrawRectangle(ImDrawList *drawList, const ImVec2 &position, const ImVec2 &bottomRightPosition,
        const ImColor &color, float rounding, float thickness) override;
};
