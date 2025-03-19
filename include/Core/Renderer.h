#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "Shader.h"
#include "Camera.h"
#include "Enemy.h"
#include "Level.h"
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Init(Camera* cam);
    void Render();
    void RenderCrosshair();
    void Shutdown();
    void AddEnemy(Enemy* enemy);
    GLuint GetVAO() const { return VAO; }
    Level* GetLevel() const { return level; }
    const std::vector<Enemy*>& GetEnemies() const { return enemies; }
private:
    GLuint VAO, VBO;
    Shader* shader;
    Camera* camera;
    std::vector<Enemy*> enemies;
    Level* level;
};

#endif