#pragma once
#include "BaseMouseButtonState.h"

class ClickedState : public BaseMouseButtonState
{
public:

    ClickedState(MouseButtons mouseButton);
    ~ClickedState() override = default;

    void CheckState() override;

};