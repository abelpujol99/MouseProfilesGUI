#pragma once

enum class MouseButtons : char;

class BaseMouseButtonState
{
public:

    virtual ~BaseMouseButtonState() = default;

    virtual void CheckState() = 0;

protected:

    BaseMouseButtonState(MouseButtons mouseButton);

    MouseButtons _mouseButton;

};
