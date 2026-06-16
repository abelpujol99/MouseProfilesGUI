#pragma once

#include "imgui.h"

class ImGuiFactory
{
public:

    ~ImGuiFactory() = default;

#pragma region Mouse

    [[nodiscard]] static float GetMouseScroll();

#pragma endregion

#pragma region Keyboard

    [[nodiscard]] static ImGuiKey GetLastKeyPressed();

    [[nodiscard]] static char GetLastCharTyped();

#pragma endregion

    [[nodiscard]] static ImFont* CreateFont(const char* fontPath);

private:

    ImGuiFactory() = default;

    static ImGuiIO& GetIO();

};