#pragma once

#include "IParentPosition.h"
#include "IParentSize.h"

struct ImDrawList;

class IDrawable : public IParentPosition, public IParentSize
{
public:

    ~IDrawable() override = default;

    virtual void Draw(ImDrawList* drawList) = 0;
};
