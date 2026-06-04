#include "Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"

void DrawEmptyRectangle::DrawRectangle(ImDrawList* drawList, const ImVec2& position, const ImVec2& bottomRightPosition,
    const ImColor& color, float rounding, float thickness)
{
    drawList->AddRect(position, bottomRightPosition, color, rounding, 0, thickness);
}
