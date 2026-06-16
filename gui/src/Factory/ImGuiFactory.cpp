#include "Factory/ImGuiFactory.h"

#include "KeyDefines.h"

ImGuiIO& ImGuiFactory::GetIO()
{
    return ImGui::GetIO();
}

#pragma region Mouse

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

        if (character < SpaceBar)
        {
            continue;
        }

        return static_cast<char>(character);
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Backspace))
    {
        return Backspace;
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Delete))
    {
        return Delete;
    }

    return 0;
}

ImFont* ImGuiFactory::CreateFont(const char* fontPath)
{
    return GetIO().Fonts->AddFontFromFileTTF(fontPath);
}
