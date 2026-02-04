#include "Factories/ImGui/ImGuiFactory.h"

#include "imgui.h"

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

#pragma endregion

ImFont* ImGuiFactory::CreateFont(const char* fontPath)
{
    return GetIO().Fonts->AddFontFromFileTTF(fontPath);
}
