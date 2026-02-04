#pragma once

#include "Managers/Gesture/MouseButton/MouseButtons.h"

class BaseMouseButtonState
{
public:

    virtual ~BaseMouseButtonState() = default;

    virtual void CheckState() = 0;

protected:

    BaseMouseButtonState(MouseButtons mouseButton);

    MouseButtons _mouseButton;

};