#pragma once
#include "backend/State/Button/IButtonInputStateAction.h"

class ButtonInputCommandStrategy;

class ButtonPressStateAction : public IButtonInputStateAction
{
public:

    ButtonPressStateAction(ButtonInputCommandStrategy* buttonInputCommand);

    void OnReceiveInputEvent() override;

private:

    ButtonInputCommandStrategy* _buttonInputCommand;

};