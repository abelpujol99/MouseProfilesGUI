#pragma once

#include "imgui.h"

namespace Utilities::Boundaries {

    [[nodiscard]] static bool IsPositionInsideBoundaries(const ImVec2& position, const ImVec2& topLeftPoint,
        const ImVec2& bottomLeftPoint);


}

inline bool Utilities::Boundaries::IsPositionInsideBoundaries(const ImVec2& position, const ImVec2& topLeftPoint,
        const ImVec2& bottomLeftPoint)
{
    return position.x > topLeftPoint.x && position.x < bottomLeftPoint.x &&
        position.y > topLeftPoint.y && position.y < bottomLeftPoint.y;
}
