#include "Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"

void DrawFilledRectangle::DrawRectangle(ImDrawList *drawList, const ImVec2 &position, const ImVec2& bottomRightPosition,
    const ImColor& color, float rounding, float thickness)
{
    drawList->AddRectFilled(position, bottomRightPosition, color, rounding, 0);
}
