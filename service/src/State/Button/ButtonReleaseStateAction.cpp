#include "State/Button/ButtonReleaseStateAction.h"

#include "Input/Strategy/ButtonInputCommandStrategy.h"
#include "State/Button/ButtonPressStateAction.h"

ButtonReleaseStateAction::ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommandStrategy(buttonInputCommand)
{}

void ButtonReleaseStateAction::OnReceiveInputEvent()
{
    _buttonInputCommandStrategy->SwitchToOffState();

    _buttonInputCommandStrategy->ChangeState(std::make_unique<ButtonPressStateAction>(_buttonInputCommandStrategy));
}