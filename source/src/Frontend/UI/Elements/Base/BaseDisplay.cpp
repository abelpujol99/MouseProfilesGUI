#include "Frontend/UI/Elements/Base/BaseDisplay.h"

BaseDisplay::BaseDisplay(bool isHidden) : _mustBeHidden(std::make_unique<bool>(isHidden)), _isHidden(isHidden)
{}

void BaseDisplay::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;

    *_mustBeHidden = _isHidden || *_isParentHidden;
}

bool BaseDisplay::IsHidden() const
{
    return _isHidden || *_isParentHidden;
}

void BaseDisplay::SetParentSizePointer(ImVec2* parentSizePointer)
{
    _parentSize = parentSizePointer;
}

ImVec2 BaseDisplay::GetParentSize() const
{
    return *_parentSize;
}

void BaseDisplay::SetIsParentHiddenPointer(bool* isParentHiddenPointer)
{
    _isParentHidden = isParentHiddenPointer;
}