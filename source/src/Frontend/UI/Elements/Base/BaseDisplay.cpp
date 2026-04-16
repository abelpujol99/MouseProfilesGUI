#include "Frontend/UI/Elements/Base/BaseDisplay.h"

BaseDisplay::BaseDisplay(bool isHidden) : _isHidden(isHidden)
{}

void BaseDisplay::SetParentSize(ImVec2* parentSize)
{
    _parentSize = parentSize;
}

ImVec2 BaseDisplay::GetParentSize() const
{
    return *_parentSize;
}

void BaseDisplay::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;
}

bool BaseDisplay::IsHidden() const
{
    return _isHidden;
}