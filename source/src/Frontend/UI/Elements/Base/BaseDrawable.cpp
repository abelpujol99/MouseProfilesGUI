#include "Frontend/UI/Elements/Base/BaseDrawable.h"

BaseDrawable::BaseDrawable(bool isHidden): BaseDisplay(isHidden)
{}

void BaseDrawable::SetParentTransform(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize)
{
    _parentPosition = parentPosition;

    _parentBottomRightPosition = parentBottomRightPosition;

    _parentSize = parentSize;
}

ImVec2 BaseDrawable::GetParentPosition() const
{
    return *_parentPosition;
}

ImVec2 BaseDrawable::GetParentBottomRightPosition() const
{
    return *_parentBottomRightPosition;
}

ImVec2 BaseDrawable::GetParentSize() const
{
    return *_parentSize;
}
