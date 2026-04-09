#include "Backend/State/Button/ButtonReleaseStateAction.h"

#include "Backend/Input/Strategy/ButtonInputCommandStrategy.h"
#include "Backend/State/Button/ButtonPressStateAction.h"

ButtonReleaseStateAction::ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommandStrategy(buttonInputCommand)
{}

void ButtonReleaseStateAction::OnReceiveInputEvent()
{
    _buttonInputCommandStrategy->SwitchToOffState();

    _buttonInputCommandStrategy->ChangeState(std::make_unique<ButtonPressStateAction>(_buttonInputCommandStrategy));
}