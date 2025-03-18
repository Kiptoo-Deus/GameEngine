#include "../include/Core/GameEngine.h"

int main(int argc, char* argv[]) {
    GameEngine engine;
    if (!engine.Init()) {
        return -1; // Initialization failed
    }

    engine.Run();
    return 0;
}