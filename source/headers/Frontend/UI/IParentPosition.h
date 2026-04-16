#pragma once

#include "imgui.h"

class IParentPosition
{
public:

    virtual ~IParentPosition() = default;

    [[nodiscard]] virtual ImVec2 GetParentPosition() const = 0;

    [[nodiscard]] virtual ImVec2 GetParentBottomRightPosition() const = 0;

};