#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Window.h"
#include "Renderer.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool Init();
    void Run();

private:
    Window* window;
    Renderer* renderer;
};

#endif // GAME_ENGINE_H
