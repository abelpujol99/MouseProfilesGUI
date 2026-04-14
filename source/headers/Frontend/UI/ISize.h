#pragma once

#include "imgui.h"

class ISize
{
public:

    virtual ~ISize() = default;

    [[nodiscard]] virtual ImVec2 GetParentSize() const = 0;

};
