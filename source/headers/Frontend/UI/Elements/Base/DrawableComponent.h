#pragma once
#include "BaseDrawable.h"

class DrawableComponent : public BaseDrawable
{
public:

    DrawableComponent(bool isHidden);

    ~DrawableComponent() override = default;
};