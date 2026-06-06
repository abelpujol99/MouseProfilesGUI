#pragma once
#include "UI/Helpers/IDrawable.h"

class IView : public IDrawable
{
public:

    ~IView() override = default;

    virtual void Enable() = 0;

    virtual void Disable() = 0;

};
