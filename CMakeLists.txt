# Minimum CMake version required
cmake_minimum_required(VERSION 3.8)

# Project definition
project(GameEngine)

# C++ Standard Configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Vcpkg Toolchain Configuration
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Source Files
set(SOURCE_FILES
    "src/main.cpp"
    "include/Core/GameEngine.cpp"
    "include/Core/Window.cpp"
    "include/Core/Shader.cpp"
    "include/Core/Renderer.cpp"
    "include/Core/Camera.cpp"
    "include/Core/Weapon.cpp"
    "include/Core/Enemy.cpp"
    "include/Core/Level.cpp"
    
)

set(HEADER_FILES
    "include/Core/GameEngine.h"
    "include/Core/Window.h"
    "include/Core/Shader.h"
    "include/Core/Renderer.h"
    "include/Core/Camera.h"
    "include/Core/Weapon.h"
    "include/Core/Enemy.h"
    "include/Core/Level.h"
    
)

# Include Directories
include_directories(
    "C:/vcpkg/installed/x64-windows/include"
    "C:/vcpkg/installed/x64-windows/include/glm"
    "C:/glad/include/glad"
    "C:/glad/src"
)

# Link Directories
link_directories(
    "C:/vcpkg/installed/x64-windows/lib"
    "C:/vcpkg/installed/x64-windows/lib/manual-link"
)

# Library Configurations
set(GLEW_LIBRARIES "C:/vcpkg/installed/x64-windows/lib/glew32.lib")

# Find Packages
find_package(OpenGL REQUIRED)

# Executable Definition
add_executable(GameEngine ${SOURCE_FILES} ${HEADER_FILES})

# Target Link Libraries
target_link_libraries(GameEngine
    OpenGL::GL
    SDL2.lib
    SDL2main.lib
    ${GLEW_LIBRARIES}
)

# Platform-specific Commands
if(WIN32)
    add_custom_command(
        TARGET GameEngine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/vcpkg/installed/x64-windows/bin/SDL2.dll"
            "C:/vcpkg/installed/x64-windows/bin/glew32.dll"
            $<TARGET_FILE_DIR:GameEngine>
        COMMENT "Copying DLLs to output directory"
    )
endif()