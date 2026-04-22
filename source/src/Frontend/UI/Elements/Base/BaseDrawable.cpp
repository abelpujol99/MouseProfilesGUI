#include "Frontend/UI/Elements/Base/BaseDrawable.h"

#include "Frontend/UI/Elements/Base/DrawableTransform.h"

BaseDrawable::BaseDrawable(bool isHidden): BaseDisplay(isHidden)
{}

void BaseDrawable::SetParentTransform(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer)
{
    _parentPosition = parentPositionPointer;
    _parentBottomRightPosition = parentBottomRightPositionPointer;

    SetParentSizePointer(parentSizePointer);
}

ImVec2 BaseDrawable::GetParentPosition() const
{
    return *_parentPosition;
}

ImVec2 BaseDrawable::GetParentBottomRightPosition() const
{
    return *_parentBottomRightPosition;
}