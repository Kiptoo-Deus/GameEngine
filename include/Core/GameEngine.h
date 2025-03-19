#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Weapon.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool Init();
    void Run();
    Level* level;
private:
    Window* window;
    Renderer* renderer;
    Camera* camera;
    Weapon* weapon;
    std::vector<Enemy*> enemies;
};

#endif