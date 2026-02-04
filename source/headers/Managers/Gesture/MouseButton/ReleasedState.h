#pragma once
#include "BaseMouseButtonState.h"

class ReleasedState : public BaseMouseButtonState
{
public:

    ReleasedState(MouseButtons mouseButton);
    ~ReleasedState() override = default;

    void CheckState() override;

};