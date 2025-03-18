# 🎮 GameEngine (OpenGL 3.3 + SDL2)
A lightweight, high-performance **3D Game Engine** built in **C++** using **OpenGL** and **SDL2**.

## 🚀 Features
✅ **Real-time 3D Rendering** (OpenGL)  
✅ **Entity-Component System (ECS)** (Planned)  
✅ **First & Third-Person Camera** (Planned)  
✅ **Basic Physics** (Planned)  
✅ **Multithreaded Performance Optimization** (Planned)  

## 🛠️ Tech Stack
- **Language:** C++ (Modern C++17/20)
- **Graphics API:** OpenGL 3.3+
- **Windowing & Input:** SDL2
- **Math & Physics:** GLM, Bullet Physics 
- **Audio:** OpenAL or FMOD

## 📥 Installation
### **1️⃣ Install Dependencies**
Make sure you have:
- [CMake](https://cmake.org/download/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/)
- [Vcpkg](https://github.com/microsoft/vcpkg) (for package management)

Then install the required libraries:
```sh
vcpkg install sdl2 glew glm opengl

git clone https://github.com/yourusername/GameEngine.git
cd GameEngine
mkdir build && cd build
cmake ..
cmake --build .

