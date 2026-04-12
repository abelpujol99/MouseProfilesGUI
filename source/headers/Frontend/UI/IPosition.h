#pragma once

#include "imgui.h"

class IPosition
{
public:

    virtual ~IPosition() = default;

    [[nodiscard]] virtual ImVec2 GetPosition() const = 0;

    [[nodiscard]] virtual ImVec2 GetBottomRightPosition() const = 0;

};