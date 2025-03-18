#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Window.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool Init();
    void Run();
    void Shutdown();

private:
    Window* window;
};

#endif // GAME_ENGINE_H
