cmake_minimum_required(VERSION 3.28.3)

function(GetProjectDir out_dir)
    set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    cmake_path(GET PROJECT_DIR PARENT_PATH ROOT_DIR)
    set(${out_dir} ${ROOT_DIR} PARENT_SCOPE)
endfunction()

function(GetSourceDir out_dir)
    set(${out_dir} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
endfunction()

function(GetProjectName project_dir out_project_name)
    cmake_path(GET project_dir PARENT_PATH ROOT_DIR)
    cmake_path(GET ROOT_DIR FILENAME ProjectId)
    string(REPLACE " " "_" ProjectId ${ProjectId})
    set(${out_project_name} ${ProjectId} PARENT_SCOPE)
endfunction()

function(GetCodeFileExtensions out_extensions)
    set(${out_extensions} "*.cpp" "*.c" "*.h" PARENT_SCOPE)
endfunction()

function(GetGlobalExpression source_dir out_global_expression)
    GetCodeFileExtensions(CODE_FILE_EXTENSIONS)
    set(GLOBAL_EXPRESSION "")

    foreach(EXTENSION IN LISTS CODE_FILE_EXTENSIONS)
        list(APPEND GLOBAL_EXPRESSION ${source_dir}/${EXTENSION})
    endforeach()

    set(${out_global_expression} ${GLOBAL_EXPRESSION} PARENT_SCOPE)
endfunction()

function(GetDirsRecursively relative_paths out_dirs)
    set(ALL_DIRS "")
    foreach (relative_path IN LISTS ${relative_paths})
        get_filename_component(ABSOLUTE_PATH ${relative_path} ABSOLUTE)
        list(APPEND ALL_DIRS ${ABSOLUTE_PATH})
        file(GLOB DIRS "${ABSOLUTE_PATH}/*")
        foreach (DIR IN LISTS DIRS)
            if (IS_DIRECTORY ${DIR})
                set(SINGLE_CHILD_LIST ${DIR})
                GetDirsRecursively(DIR SUB_DIRS)
                list(APPEND ALL_DIRS ${SUB_DIRS})
            endif ()
        endforeach ()
    endforeach ()
    set(${out_dirs} ${ALL_DIRS} PARENT_SCOPE)
endfunction()

function(GetCodeFiles source_dir out_code_files)
    GetGlobalExpression(${source_dir} GLOBAL_EXPRESSION)
    cmake_path(GET source_dir PARENT_PATH source_dir)
    file(GLOB_RECURSE CODE_FILES CONFIGURE_DEPENDS ${GLOBAL_EXPRESSION})
    set(RELATIVE_CODE_FILES "")
    foreach (code_file IN LISTS CODE_FILES)
        file(RELATIVE_PATH relative_path ${source_dir} ${code_file})
        list(APPEND RELATIVE_CODE_FILES ${relative_path})
    endforeach ()
    set(${out_code_files} ${RELATIVE_CODE_FILES} PARENT_SCOPE)
endfunction()

function(OrganizeIDECodeFiles source_dir code_files)
    source_group(TREE ${source_dir} FILES ${code_files})
endfunction()

function(IncludeDirectoriesToTarget project_name scope include_dirs)
    foreach(include_dir IN LISTS ${include_dirs})
        target_include_directories(${project_name} ${scope} ${include_dir})
    endforeach ()
endfunction()

function(LinkLibrariesToTarget project_name scope libraries)
    foreach(library IN LISTS ${libraries})
        target_link_libraries(${project_name} ${scope} ${library})
    endforeach ()
endfunction()

function(SetCompileOptionsGNUToTarget project_name)
    set_target_properties(${project_name} PROPERTIES CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER ON)
    add_compile_options(-Werror)
endfunction()

function(SetLibraryCppStandardToTarget target_name cpp_standard)
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD ${cpp_standard}
        CXX_STANDARD_REQUIRED ON)
endfunction()

#Resources
function(CopyResourcesToBuild source_dir)
    file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS ${source_dir}/resources/*)
    add_custom_target(copy_resources ALL
        DEPENDS ${RESOURCE_FILES}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
    add_dependencies(${PROJECT_NAME} copy_resources)
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_BINARY_DIR}/resources"
    )
endfunction()

#ImGui
function(FetchImGui source_dir out_imgui_source_dir)
    set(FETCHCONTENT_BASE_DIR ${source_dir}/libraries/ImGui)
    FetchContent_Declare(
            ImGui
            GIT_REPOSITORY https://github.com/ocornut/imgui
            GIT_TAG 76860017d51f25f943a1e607ab795b3615acefb5 #1.92.5
    )

    FetchContent_MakeAvailable(ImGui)
    set(${out_imgui_source_dir} ${imgui_SOURCE_DIR} PARENT_SCOPE)
endfunction()

function(AddImGuiTarget imgui_source_dir)
    add_library(imgui STATIC
        ${imgui_source_dir}/imgui.cpp
        ${imgui_source_dir}/imgui_draw.cpp
        ${imgui_source_dir}/imgui_tables.cpp
        ${imgui_source_dir}/imgui_widgets.cpp
        ${imgui_source_dir}/backends/imgui_impl_glfw.cpp
        ${imgui_source_dir}/backends/imgui_impl_opengl3.cpp)

    IncludeDirectoriesToTarget(imgui PUBLIC imgui_source_dir)
endfunction()

#Glad
function(AddGladTarget source_dir)
    set(GLAD_DIR ${source_dir}/libraries/glad)
    add_library(glad STATIC
            ${GLAD_DIR}/src/glad.c)

    target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
endfunction()

#Stb
function(FetchStb source_dir out_stb_source_dir)
    set(FETCHCONTENT_BASE_DIR ${source_dir}/libraries/stb)
    FetchContent_Declare(
            stb
            GIT_REPOSITORY https://github.com/nothings/stb
            GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
    )

    FetchContent_MakeAvailable(stb)
    set(${out_stb_source_dir} ${stb_SOURCE_DIR} PARENT_SCOPE)
endfunction()

function(AddStbTarget stb_source_dir)
    add_library(stb INTERFACE)
    IncludeDirectoriesToTarget(stb INTERFACE stb_source_dir)
endfunction()