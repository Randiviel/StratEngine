cmake_minimum_required(VERSION 3.20)
project(ImGui)
set(CMAKE_CXX_STANDARD 23)

set(PROJECT_PATH C:/Users/yiss/Desktop/Development/StratEngine)

add_library(imgui
    STATIC
        imgui.h
        imgui.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui_demo.cpp
        backends/imgui_impl_glfw.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.h
        backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR} 
${CMAKE_CURRENT_SOURCE_DIR}/backends
${PROJECT_PATH}/vendor/GLFW/include/GLFW

)
