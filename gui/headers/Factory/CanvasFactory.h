#pragma once

#include "MVP/View/BaseView.h"

class Rectangle;
class Text;

class CanvasFactory
{
public:

    /*[[nodiscard]] static std::unique_ptr<IView> CreateDevicesCanvas(bool isHidden);

    [[nodiscard]] static std::unique_ptr<IView> CreateProfileCanvas(bool isHidden);*/

private:

    static std::unique_ptr<Rectangle> GetRectangle(ImColor color);

    static std::unique_ptr<Text> GetText(std::string string);
};
