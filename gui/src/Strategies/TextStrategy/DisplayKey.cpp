#include "Strategies/TextStrategy/DisplayKey.h"

#include "Managers/Input/InputManager.h"
#include "UI/Elements/Intermediate/Text.h"

void DisplayKey::StartProcessData()
{
    _onKeyPressedAction = InputManager::GetInstance().SubscribeToKeyPressed([&](const char* keyPressed) {

        if (!_text->GetText().empty())
        {
            _text->AddText("+");
        }

        _text->AddText(std::string(keyPressed));
    });
}

void DisplayKey::StopProcessData()
{
    InputManager::GetInstance().UnsubscribeToKeyPressed(std::move(_onKeyPressedAction));
}