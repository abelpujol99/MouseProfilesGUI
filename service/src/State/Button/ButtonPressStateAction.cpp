#include "State/Button/ButtonPressStateAction.h"

#include "Input/Strategy/ButtonInputCommandStrategy.h"
#include "State/Button/ButtonReleaseStateAction.h"

ButtonPressStateAction::ButtonPressStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommand(buttonInputCommand)
{}

void ButtonPressStateAction::OnReceiveInputEvent()
{
    _buttonInputCommand->Press();
    _buttonInputCommand->DelegateHoldCommand();

    _buttonInputCommand->ChangeState(std::make_unique<ButtonReleaseStateAction>(_buttonInputCommand));
}