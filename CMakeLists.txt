cmake_minimum_required(VERSION 3.8)

project(GameEngine)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# Specify the vcpkg toolchain file (for automatic package finding)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Include directories for GLEW and SDL2
include_directories(C:/vcpkg/installed/x64-windows/include)

# Link directories for GLEW and SDL2
link_directories(C:/vcpkg/installed/x64-windows/lib/manual-link)
link_directories(C:/vcpkg/installed/x64-windows/lib)

# Manually set GLEW include and lib directories
set(GLEW_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
set(GLEW_LIBRARIES "C:/vcpkg/installed/x64-windows/lib/glew32.lib")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Manually set SDL2 paths (from PulseHubCpp-copied my previous repo cmakelist😂😜)
include_directories(C:/vcpkg/installed/x64-windows/include)
include_directories(C:/vcpkg/installed/x64-windows/include/glm)
include_directories(C:/glad/include/glad)
link_directories(C:/vcpkg/installed/x64-windows/lib)
include_directories(C:/glad/src)
# Add executable
add_executable(GameEngine "src/main.cpp" "include/Core/GameEngine.cpp" "include/Core/GameEngine.h" "include/Core/Window.h" "include/Core/Window.cpp" "include/Core/Shader.h" "include/Core/Shader.cpp" "include/Core/Renderer.h" "include/Core/Renderer.cpp" "include/Core/Camera.h" "include/Core/Camera.cpp" "include/Core/Weapon.h" "include/Core/Weapon.cpp" "include/Core/Enemy.h" "include/Core/Enemy.cpp")

# Link libraries (include GLEW and SDL2 manually)
target_link_libraries(GameEngine OpenGL::GL SDL2.lib SDL2main.lib ${GLEW_LIBRARIES})

if(WIN32)
    add_custom_command(TARGET GameEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/installed/x64-windows/bin/SDL2.dll"
        "C:/vcpkg/installed/x64-windows/bin/glew32.dll"
        $<TARGET_FILE_DIR:GameEngine>)
endif()