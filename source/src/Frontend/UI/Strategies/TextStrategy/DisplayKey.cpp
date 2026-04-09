#include "Frontend/UI/Strategies/TextStrategy/DisplayKey.h"

#include "Frontend/Managers/Input/InputManager.h"
#include "Frontend/UI/Basic/Text.h"

void DisplayKey::StartProcessData()
{
    _onTypingWeakAction = InputManager::GetInstance().SubscribeToCurrentTypedKeyObserver([&](Key key) {

        if (!_text->GetText().empty())
        {
            _text->AddText("+");
        }

        _text->AddText(std::string(ImGui::GetKeyName(key)));
    });
}

void DisplayKey::StopProcessData()
{
    InputManager::GetInstance().UnsubscribeToCurrentTypedKeyObserver(_onTypingWeakAction);
}