cmake_minimum_required(VERSION 4.0)
project(MouseProfilesGUI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        libs
        libs/glad/include/glad
        libs/glad/include/KHR
        libs/ImGuiAPI
        libs/ImGuiAPI/backends
        headers
        headers/Factories
        headers/Managers
        headers/UI
)

set(SOURCES
        main.cpp
        libs/glad/src/glad.c
        libs/ImGuiAPI/imgui.cpp
        libs/ImGuiAPI/imgui_draw.cpp
        libs/ImGuiAPI/imgui_tables.cpp
        libs/ImGuiAPI/imgui_widgets.cpp
        libs/ImGuiAPI/backends/imgui_impl_glfw.cpp
        libs/ImGuiAPI/backends/imgui_impl_opengl3.cpp
        src/Factories/DrawableFactory.cpp
        src/Managers/ApplicationManager.cpp
        src/Managers/DrawManager.cpp
        src/Managers/WindowManager.cpp
        src/UI/Drawable.cpp
        src/UI/Texture.cpp
)

add_executable(MouseProfilesGUI ${SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if(GLFW_FOUND)
        include_directories(${GLFW_INCLUDE_DIRS})
        target_link_libraries(MouseProfilesGUI ${GLFW_LIBRARIES})
else()
        message(FATAL_ERROR "GLFW not found")
endif()

target_link_libraries(MouseProfilesGUI GL dl pthread)