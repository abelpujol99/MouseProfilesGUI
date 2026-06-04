#pragma once
#include <memory>

#include "imgui.h"

class DrawableTransform
{
public:

    virtual ~DrawableTransform() = default;

protected:

    std::unique_ptr<ImVec2> _position {std::make_unique<ImVec2>()};

    std::unique_ptr<ImVec2> _bottomRightPosition {std::make_unique<ImVec2>()};

    std::unique_ptr<ImVec2> _size {std::make_unique<ImVec2>()};

};