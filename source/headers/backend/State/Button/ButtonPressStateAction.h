#pragma once
#include "backend/State/Button/IButtonInputStateAction.h"

class ButtonInputCommandStrategy;

class ButtonPressStateAction : public IButtonInputStateAction
{
private:

    ButtonInputCommandStrategy* _buttonInputCommand;

public:

    ButtonPressStateAction(ButtonInputCommandStrategy* buttonInputCommand);

    void OnReceiveInputEvent() override;
};