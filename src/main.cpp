#include "../include/Core/GameEngine.h"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
    GameEngine engine;
    if (!engine.Init()) {
        return -1; // Initialization failed
    }

    engine.Run();
    return 0;
}