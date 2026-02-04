#include <ButtonReleaseStateAction.h>

#include <ButtonInputCommandStrategy.h>
#include <ButtonPressStateAction.h>

ButtonReleaseStateAction::ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommandStrategy(buttonInputCommand)
{}

void ButtonReleaseStateAction::OnReceiveInputEvent()
{
    _buttonInputCommandStrategy->SwitchToOffState();

    _buttonInputCommandStrategy->ChangeState(std::make_unique<ButtonPressStateAction>(_buttonInputCommandStrategy));
}