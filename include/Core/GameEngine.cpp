#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    window = new Window("FPS Game Engine", 800, 600);
    camera = new Camera();
    renderer = new Renderer();
    weapon = new Weapon(camera);
}

GameEngine::~GameEngine() {
    delete weapon;
    delete renderer;
    delete camera;
    delete window;
}

bool GameEngine::Init() {
    if (!window->Init()) {
        return false;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);
    renderer->Init(camera);
    weapon->Init();
    return true;
}

void GameEngine::Run() {
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (true) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                std::cout << "Left mouse button clicked!" << std::endl;
                weapon->Shoot();
            }
        }

        int x, y;
        SDL_GetRelativeMouseState(&x, &y);
        camera->ProcessMouse((float)x, (float)y);
        camera->ProcessKeyboard(deltaTime);

        weapon->Update(deltaTime); 
        renderer->Render();
        weapon->Render();
        window->SwapBuffers();
    }
}