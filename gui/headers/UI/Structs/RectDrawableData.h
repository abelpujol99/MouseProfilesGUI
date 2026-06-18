#pragma once
#include "Utilities/UI/Anchors.h"
#include "Utilities/UI/Pivot.h"

struct RectDrawableData
{
    Anchors anchors;
    Pivot pivot;
    ImVec2 relativePosition;
    ImVec2 desiredSize;
};
