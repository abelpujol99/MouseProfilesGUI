#pragma once

#include "imgui.h"

class ImGuiFactory
{
public:

    ~ImGuiFactory() = default;

    [[nodiscard]] static ImFont* CreateFont(const char* fontPath);

private:

    ImGuiFactory() = default;

    static ImGuiIO& GetIO();

};