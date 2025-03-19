#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    window = new Window("FPS Game Engine", 800, 600);
    camera = new Camera();
    renderer = new Renderer();
}

GameEngine::~GameEngine() {
    delete renderer;
    delete camera;
    delete window;
}

bool GameEngine::Init() {
    if (!window->Init()) {
        return false;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE); // Lock mouse
    renderer->Init(camera);
    return true;
}

void GameEngine::Run() {
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (true) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        window->PollEvents();

        // Mouse movement
        int x, y;
        SDL_GetRelativeMouseState(&x, &y);
        camera->ProcessMouse((float)x, (float)y);
        camera->ProcessKeyboard(deltaTime);

        renderer->Render();
        window->SwapBuffers();
    }
}