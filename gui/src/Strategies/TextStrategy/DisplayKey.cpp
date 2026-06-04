#include "Strategies/TextStrategy/DisplayKey.h"

#include "Managers/Input/TypeManager.h"
#include "UI/Elements/Intermediate/Text.h"

void DisplayKey::StartProcessData()
{
    _onTypingWeakAction = TypeManager::GetInstance().SubscribeToCurrentTypedKeyObserver([&](Key key) {

        if (!_text->GetText().empty())
        {
            _text->AddText("+");
        }

        _text->AddText(std::string(ImGui::GetKeyName(key)));
    });
}

void DisplayKey::StopProcessData()
{
    TypeManager::GetInstance().UnsubscribeToCurrentTypedKeyObserver(_onTypingWeakAction);
}