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