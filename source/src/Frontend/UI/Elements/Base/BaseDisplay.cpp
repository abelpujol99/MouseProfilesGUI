#include "Frontend/UI/Elements/Base/BaseDisplay.h"

BaseDisplay::BaseDisplay(bool isHidden) : _isHidden(isHidden)
{}

void BaseDisplay::SetIsHidden(bool isHidden)
{
    _isHidden = isHidden;

    UpdateVisibility();
}

bool BaseDisplay::IsHidden() const
{
    return *_mustBeHidden;
}

void BaseDisplay::UpdateVisibility()
{
    *_mustBeHidden = *_isParentHidden || _isHidden;
}

bool BaseDisplay::MustBeHidden() const
{
    return *_mustBeHidden;
}

void BaseDisplay::SetParentSize(ImVec2* parentSize)
{
    _parentSize = parentSize;
}

ImVec2 BaseDisplay::GetParentSize() const
{
    return *_parentSize;
}

void BaseDisplay::SetParentIsHidden(bool* isParentHidden)
{
    _isParentHidden = isParentHidden;

    UpdateVisibility();
}

bool BaseDisplay::IsParentHidden() const
{
    return *_isParentHidden;
}