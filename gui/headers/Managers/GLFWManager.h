 #pragma once

#include "Utilities/WaylandContext.h"

 struct GLFWwindow;

class GLFWManager
{
public:

    static GLFWwindow* CreateWindow(int width, int height, const char* windowName);

    static WaylandContext GetWaylandContext(const wl_registry_listener* registryListener);

    static void PrepareWindow();

    static void CleanseWindow(GLFWwindow* window);

    static void CleanseInput(const WaylandContext& waylandContext) noexcept;

private:

    static void GlfwErrorCallback(int error, const char* description);
};