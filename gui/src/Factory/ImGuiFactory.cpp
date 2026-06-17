#include "Factory/ImGuiFactory.h"

ImGuiIO& ImGuiFactory::GetIO()
{
    return ImGui::GetIO();
}

ImFont* ImGuiFactory::CreateFont(const char* fontPath)
{
    return GetIO().Fonts->AddFontFromFileTTF(fontPath);
}