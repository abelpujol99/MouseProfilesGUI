#include "Drawable.h"

Drawable::Drawable(int positionX, int positionY) : _topLeftPosition(positionX, positionY)
{}

void Drawable::SetSize(int width, int height)
{
    _size.x = width;
    _size.y = height;

    _bottomRightPosition.x = _topLeftPosition.x + _size.x;
    _bottomRightPosition.y = _topLeftPosition.y + _size.y;
}
