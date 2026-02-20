#include "Factories/ImGui/ImGuiFactory.h"

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

#pragma endregion

ImFont* ImGuiFactory::CreateFont(const char* fontPath)
{
    return GetIO().Fonts->AddFontFromFileTTF(fontPath);
}
