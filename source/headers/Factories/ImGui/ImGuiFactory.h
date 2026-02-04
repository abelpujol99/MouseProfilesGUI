#pragma once
#include "Managers/Gesture/MouseButton/MouseButtons.h"

struct ImGuiIO;
struct ImVec2;
struct ImFont;

class ImGuiFactory
{
public:

    ~ImGuiFactory() = default;

#pragma region Mouse

    [[nodiscard]] static const int GetMouseMaxButtons();

    [[nodiscard]] static const bool IsMouseButtonPressed(MouseButtons mouseButton);
    [[nodiscard]] static const bool IsMouseButtonReleased(MouseButtons mouseButton);

    [[nodiscard]] static ImVec2 GetMousePosition();

#pragma endregion

    [[nodiscard]] static ImFont* CreateFont(const char* fontPath);

private:

    ImGuiFactory() = default;

    [[nodiscard]] static ImGuiIO& GetIO();

};