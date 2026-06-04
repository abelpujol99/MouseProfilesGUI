#pragma once

#include "imgui.h"

class IParentSize
{
public:

    virtual ~IParentSize() = default;

    [[nodiscard]] virtual ImVec2 GetParentSize() const = 0;

};
