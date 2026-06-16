 #pragma once

#include "Utilities/WaylandSettings.h"

 struct GLFWwindow;

class GLFWManager
{
public:

    static GLFWwindow* CreateWindow(int width, int height, const char* windowName);

    static WaylandSettings GetWaylandSettings(const wl_registry_listener* registryListener);

    static void PrepareWindow();

    static void CleanseWindow(GLFWwindow* window);

    static void CleanseInput(const WaylandSettings& waylandSettings) noexcept;

private:

    static void GlfwErrorCallback(int error, const char* description);
};