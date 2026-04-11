#pragma once
#include <memory>
#include <string>

#include "Frontend/UI/Drawable.h"

struct DrawablePosition;

class ScreenFactory
{
public:
    [[nodiscard]] static std::unique_ptr<Drawable> CreateProfileScreen(DrawablePosition&& screenDrawablePosition, std::string peripheralName);
};
