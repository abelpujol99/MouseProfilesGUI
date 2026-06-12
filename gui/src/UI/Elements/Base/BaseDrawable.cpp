#include "UI/Elements/Base/BaseDrawable.h"

BaseDrawable::BaseDrawable(bool isHidden): BaseDisplay(isHidden)
{}

void BaseDrawable::SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
    ImVec2* parentSizePointer, bool* isParentHiddenPointer)
{
    _parentPosition = parentPositionPointer;
    _parentBottomRightPosition = parentBottomRightPositionPointer;

    SetParentSizePointer(parentSizePointer);

    SetIsParentHiddenPointer(isParentHiddenPointer);
}

ImVec2 BaseDrawable::GetParentPosition() const
{
    return *_parentPosition;
}

ImVec2 BaseDrawable::GetParentBottomRightPosition() const
{
    return *_parentBottomRightPosition;
}