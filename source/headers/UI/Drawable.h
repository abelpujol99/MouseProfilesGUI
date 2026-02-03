#pragma once

#include "imgui.h"

struct ImDrawList;

class Drawable
{
protected:

    ImVec2 _topLeftPosition;
    ImVec2 _size;
    ImVec2 _bottomRightPosition;

    Drawable(int positionX, int positionY);

    void SetSize(int width, int height);

public:

    virtual ~Drawable() = default;

    virtual void Draw(ImDrawList* drawList) = 0;
};
