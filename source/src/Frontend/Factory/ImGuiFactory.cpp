#include "Frontend/Factory/ImGuiFactory.h"

#include "Frontend/Managers/Input/MouseButton/MouseButtons.h"
#include "Frontend/KeyDefines.h"

ImGuiIO& ImGuiFactory::GetIO()
{
    return ImGui::GetIO();
}

#pragma region Mouse

const int ImGuiFactory::GetMouseMaxButtons()
{
    return static_cast<int>(MouseButtons::COUNT);
}

const bool ImGuiFactory::IsMouseButtonPressed(MouseButtons mouseButton)
{
    return GetIO().MouseDown[static_cast<int>(mouseButton)];
}

const bool ImGuiFactory::IsMouseButtonReleased(MouseButtons mouseButton)
{
    return GetIO().MouseReleased[static_cast<int>(mouseButton)];
}

ImVec2 ImGuiFactory::GetMousePosition()
{
    return GetIO().MousePos;
}

float ImGuiFactory::GetMouseScroll()
{
    return GetIO().MouseWheel;
}

#pragma endregion

ImGuiKey ImGuiFactory::GetLastKeyPressed()
{
    for (int key {ImGuiKey_NamedKey_BEGIN}; key < ImGuiKey_NamedKey_END; ++key)
    {
        const ImGuiKey& imGuiKey {static_cast<ImGuiKey>(key)};

        if (!ImGui::IsKeyPressed(imGuiKey))
        {
            continue;
        }

        return imGuiKey;
    }

    return ImGuiKey_None;
}

char ImGuiFactory::GetLastCharTyped()
{
    ImGuiIO& io {GetIO()};

    for (int i {0}; i < io.InputQueueCharacters.Size; ++i)
    {
        ImWchar character {io.InputQueueCharacters[i]};

        if ((character < CHAR_0 || character > CHAR_9) &&
            (character < CHAR_A || character > CHAR_Z) &&
            character != CHAR_PLUS)
        {
            continue;
        }

        return static_cast<char>(character);
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Backspace))
    {
        return Backspace;
    }

    return 0;
}

ImFont* ImGuiFactory::CreateFont(const char* fontPath)
{
    return GetIO().Fonts->AddFontFromFileTTF(fontPath);
}
