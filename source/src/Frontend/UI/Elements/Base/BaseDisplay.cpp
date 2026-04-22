#include "Frontend/UI/Elements/Base/BaseDisplay.h"

BaseDisplay::BaseDisplay(bool isHidden) : _isHidden(isHidden)
{}

void BaseDisplay::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

bool BaseDisplay::IsHidden() const
{
    return _isHidden;
}

void BaseDisplay::SetParentSizePointer(ImVec2* parentSizePointer)
{
    _parentSize = parentSizePointer;
}

ImVec2 BaseDisplay::GetParentSize() const
{
    return *_parentSize;
}