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
    void TakeDamage(float damage) { health -= damage; if (health < 0) health = 0; }
    float GetHealth() const { return health; }

private:
    Window* window;
    Renderer* renderer;
    Camera* camera;
    Weapon* weapon;
    std::vector<Enemy*> enemies;
    Level* level;
    float health = 100.0f; 
};

#endif