#include "Frontend/UI/Elements/Base/DrawableComponent.h"

DrawableComponent::DrawableComponent(bool isHidden) :
        BaseDrawable(isHidden)
{}

void DrawableComponent::SetBottomRightPositionPointer(ImVec2* bottomRightPositionPointer)
{
    _bottomRightPosition = bottomRightPositionPointer;
}

ImVec2 DrawableComponent::GetBottomRightPosition() const
{
    return *_bottomRightPosition;
}