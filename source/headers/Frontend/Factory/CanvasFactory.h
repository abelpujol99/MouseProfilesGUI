#pragma once

#include "Frontend/UI/Elements/Complex/Canvas.h"

class Rectangle;
class Text;

class CanvasFactory
{
public:

    [[nodiscard]] static std::unique_ptr<Canvas> CreateProfileCanvas(bool isHidden);

private:

    static void ShowLinesX(void* rect);

    static std::unique_ptr<Rectangle> GetRectangle(ImColor color);

    static std::unique_ptr<Text> GetText(std::string string);
};
