cmake_minimum_required(VERSION 3.28.3)

include("Utilities.cmake")
include(FetchContent)

GetProjectDir(PROJECT_DIR)

#######################
########SHARED#########
#######################
set(shared_target_dir shared)

GetSourceDir(SHARED_SOURCE_DIR ${shared_target_dir})

add_library(shared INTERFACE)

set(SHARED_INCLUDE
        ${shared_target_dir}/defines
        ${shared_target_dir}/headers
        ${shared_target_dir}/usings)

IncludeDirectoriesToTarget(shared INTERFACE SHARED_INCLUDE)

#######################
########SERVICE########
#######################
set(service_target_dir service)

GetSourceDir(SERVICE_SOURCE_DIR ${service_target_dir})
GetProjectName(${SERVICE_SOURCE_DIR} SERVICE_PROJECT_NAME)

project(${SERVICE_PROJECT_NAME})

set(SERVICE_SOURCES ${service_target_dir}/headers ${service_target_dir}/src)
set(SERVICE_CODE_FILES "")
foreach (source IN LISTS SERVICE_SOURCES)
        GetCodeFiles(${PROJECT_DIR} ${source} SERVICE_SOURCE_CODE_FILES)
        list(APPEND SERVICE_CODE_FILES ${SERVICE_SOURCE_CODE_FILES})
endforeach ()

OrganizeIDECodeFiles(${PROJECT_DIR} SERVICE_CODE_FILES)

add_executable(${SERVICE_PROJECT_NAME} ${SERVICE_CODE_FILES})

#Resources
CopyResourcesToBuild(${SERVICE_PROJECT_NAME} ${SERVICE_SOURCE_DIR})

#Includes
set(SERVICE_INCLUDES
        ${service_target_dir}/headers
        ${service_target_dir}/usings)

IncludeDirectoriesToTarget(${SERVICE_PROJECT_NAME} PRIVATE SERVICE_INCLUDES)

set(SERVICE_LIBRARIES
        pthread
        shared)

LinkLibrariesToTarget(${SERVICE_PROJECT_NAME} PRIVATE SERVICE_LIBRARIES)

#CPP
SetLibraryCppStandardToTarget(${SERVICE_PROJECT_NAME} 20)

#CompilerOptions
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        SetCompileOptionsGNUToTarget(${SERVICE_PROJECT_NAME})
endif ()

#######################
##########GUI##########
#######################
set(gui_target_dir gui)
GetSourceDir(GUI_SOURCE_DIR ${gui_target_dir})
GetProjectName(${GUI_SOURCE_DIR} GUI_PROJECT_NAME)

project(${GUI_PROJECT_NAME})

#GLFW
FetchGLFW(${GUI_SOURCE_DIR} GLFW_SOURCE_DIR)

#ImGui
FetchImGui(${GUI_SOURCE_DIR} IMGUI_SOURCE_DIR)
AddImGuiTarget(${IMGUI_SOURCE_DIR} ${GLFW_SOURCE_DIR})

#Glad
AddGladTarget(${GUI_SOURCE_DIR})

#Stb
FetchStb(${GUI_SOURCE_DIR} STB_SOURCE_DIR)
AddStbTarget(${STB_SOURCE_DIR})

set(GUI_SOURCES ${gui_target_dir}/headers ${gui_target_dir}/src)
set(GUI_CODE_FILES "")
foreach (source IN LISTS GUI_SOURCES)
        GetCodeFiles(${PROJECT_DIR} ${source} GUI_SOURCE_CODE_FILES)
        list(APPEND GUI_CODE_FILES ${GUI_SOURCE_CODE_FILES})
endforeach ()

OrganizeIDECodeFiles(${PROJECT_DIR} GUI_CODE_FILES)

add_executable(${GUI_PROJECT_NAME} ${GUI_CODE_FILES})

#Resources
CopyResourcesToBuild(${GUI_PROJECT_NAME} ${GUI_SOURCE_DIR})

#Includes
set(GUI_INCLUDES
        ${gui_target_dir}/defines
        ${gui_target_dir}/headers
        ${gui_target_dir}/usings
        ${gui_target_dir}/libraries)

IncludeDirectoriesToTarget(${GUI_PROJECT_NAME} PRIVATE GUI_INCLUDES)

set(GUI_LIBRARIES
        GL
        dl
        pthread
        imgui
        glfw
        glad
        stb
        shared)

LinkLibrariesToTarget(${GUI_PROJECT_NAME} PRIVATE GUI_LIBRARIES)

#CPP
SetLibraryCppStandardToTarget(${GUI_PROJECT_NAME} 20)

#CompilerOptions
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        SetCompileOptionsGNUToTarget(${GUI_PROJECT_NAME})
endif ()