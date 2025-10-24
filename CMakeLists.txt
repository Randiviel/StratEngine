cmake_minimum_required(VERSION 3.20)
make_directory(build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(CMAKE_CXX_STANDARD 23)
#-------------------------------------------
project(MyProject VERSION 1.0 LANGUAGES C CXX)
find_package(OpenGL REQUIRED)
#-------------------------------------------
add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/entt)
#-------------------------------------------
add_library(Glad_lib
    STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/src/glad.c
    )

target_include_directories(Glad_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include/
    )
#-------------------------------------------

file(GLOB_RECURSE STRATENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Renderer/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Event/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Window/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Scene/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Architecture/OpenGL/*.cpp"
)

add_library(StratEngine 
    STATIC
        ${STRATENGINE_SOURCES}
    )

target_link_libraries(StratEngine 
    PUBLIC 
        glfw
        OpenGL::GL
        imgui
        Glad_lib
        glm
        stb_image
        spdlog
        EnTT
        )

target_include_directories(StratEngine 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine
        ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include/GLFW
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt/src/
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor
        )

target_precompile_headers(StratEngine 
    PRIVATE
    StratEngine/src/pchstrat.h
    )
#-------------------------------------------

add_executable(MyApp Sandbox/Sandbox.cpp)
target_sources(MyApp PUBLIC Sandbox/EditorLayer/EditorLayer.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/Shaders DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

target_link_libraries(MyApp PRIVATE StratEngine)

target_include_directories(MyApp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/vendor/imgui)


#-------------------------------------------
# Old way of adding files to StratEngine library
# add_library(StratEngine 
#     STATIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Window/Window.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Window/WindowsWindow/WindowsWindow.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Window/WindowsWindow/WindowsWindow.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/Application.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/Application.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/StratConfig.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/Entrypoint.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/Layer.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Core/Layer.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Renderer/Shader.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Renderer/Shader.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Renderer/VertexArray.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/StratEngine/src/Renderer/VertexArray.cpp
#         # GLAD files
#         ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include/glad/glad.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include/KHR/khrplatform.h
#         )