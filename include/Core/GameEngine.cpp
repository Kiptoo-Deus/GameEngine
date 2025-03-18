#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    window = new Window("Game Engine 3D", 800, 600);
    renderer = new Renderer();
}

GameEngine::~GameEngine() {
    delete renderer;
    delete window;
}

bool GameEngine::Init() {
    std::cout << "Initializing Game Engine..." << std::endl;

    if (!window->Init()) {
        return false;
    }

    renderer->Init();
    return true;
}

void GameEngine::Run() {
    std::cout << "Running Game Engine..." << std::endl;

    while (true) {
        window->PollEvents();

        renderer->Render();
        window->SwapBuffers();
    }
}
