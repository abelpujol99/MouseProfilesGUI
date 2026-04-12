#include "Frontend/UI/Elements/Base/BaseDrawable.h"

BaseDrawable::BaseDrawable(bool isHidden): BaseDisplay(isHidden)
{}

ImVec2 BaseDrawable::GetPosition() const
{
    return *_parentPosition;
}

ImVec2 BaseDrawable::GetSize() const
{
    return *_parentSize;
}

void BaseDrawable::SetParentTransform(ImVec2* parentPosition, ImVec2* parentSize)
{
    _parentPosition = parentPosition;

    _parentSize = parentSize;
}
