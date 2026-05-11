cmake_minimum_required(VERSION 3.28.3)

include("Utilities.cmake")
include(FetchContent)

GetProjectDir(PROJECT_DIR)
GetSourceDir(SOURCE_DIR)
GetProjectName(${PROJECT_DIR} PROJECT_NAME)

project(${PROJECT_NAME})

#GLFW
FetchGLFW(${SOURCE_DIR} GLFW_SOURCE_DIR)

#ImGui
FetchImGui(${SOURCE_DIR} IMGUI_SOURCE_DIR)
AddImGuiTarget(${IMGUI_SOURCE_DIR} ${GLFW_SOURCE_DIR})

#Glad
AddGladTarget(${SOURCE_DIR})

#Stb
FetchStb(${SOURCE_DIR} STB_SOURCE_DIR)
AddStbTarget(${STB_SOURCE_DIR})

set(SOURCES headers src)
set(CODE_FILES "")
foreach (source IN LISTS SOURCES)
        GetCodeFiles(${SOURCE_DIR}/${source} SOURCE_CODE_FILES)
        list(APPEND CODE_FILES ${SOURCE_CODE_FILES})
endforeach ()

OrganizeIDECodeFiles(${SOURCE_DIR} CODE_FILES)

add_executable(${PROJECT_NAME} ${CODE_FILES})

#Resources
CopyResourcesToBuild(${SOURCE_DIR})

#Includes
set(INCLUDES
        defines
        headers
        usings
        libraries)

IncludeDirectoriesToTarget(${PROJECT_NAME} PUBLIC INCLUDES)

set(LIBRARIES
        GL
        dl
        pthread
        imgui
        glfw
        glad
        stb)

LinkLibrariesToTarget(${PROJECT_NAME} PUBLIC LIBRARIES)

#CPP
SetLibraryCppStandardToTarget(${PROJECT_NAME} 20)

#CompilerOptions
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        SetCompileOptionsGNUToTarget(${PROJECT_NAME})
endif ()