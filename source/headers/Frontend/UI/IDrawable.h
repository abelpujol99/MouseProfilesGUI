#pragma once

#include "IPosition.h"
#include "ISize.h"

struct ImDrawList;

class IDrawable : public IPosition, public ISize
{
public:

    ~IDrawable() override = default;

    virtual void Draw(ImDrawList* drawList) = 0;
};
