#include "Frontend/UI/Elements/Base/BaseDrawable.h"

BaseDrawable::BaseDrawable(bool isHidden) :
        BaseDisplay(isHidden)
{}

void BaseDrawable::SetParentAttributes(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize,
        bool* isParentHidden)
{
    _parentPosition = parentPosition;

    _parentBottomRightPosition = parentBottomRightPosition;

    SetParentSize(parentSize);

    SetParentIsHidden(isParentHidden);

    UpdateVisibility();
}

ImVec2 BaseDrawable::GetParentPosition() const
{
    return *_parentPosition;
}

ImVec2 BaseDrawable::GetParentBottomRightPosition() const
{
    return *_parentBottomRightPosition;
}