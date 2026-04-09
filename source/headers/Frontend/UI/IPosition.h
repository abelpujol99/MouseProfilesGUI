#pragma once

#include "imgui.h"

class IPosition
{
public:

    virtual ~IPosition() = default;

    [[nodiscard]] virtual ImVec2* GetPosition() const = 0;

};
