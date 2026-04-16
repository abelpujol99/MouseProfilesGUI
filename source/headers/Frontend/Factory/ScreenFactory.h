#pragma once

#include "Frontend/UI/Elements/Complex/Screen.h"

class Rectangle;
class Text;

class ScreenFactory
{
public:

    [[nodiscard]] static std::unique_ptr<Screen> CreateProfileScreen(bool isHidden);

private:

    static void ShowLinesX(void* rect);

    static std::unique_ptr<Rectangle> GetRectangle(ImColor color);

    static std::unique_ptr<Text> GetText(std::string string);
};
