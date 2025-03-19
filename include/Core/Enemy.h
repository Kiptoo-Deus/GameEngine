#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Level.h" 

class Enemy {
public:
    Enemy(glm::vec3 position);
    void Init(GLuint sharedVAO, Level* lvl = nullptr);
    void Update(float deltaTime);
    void Render(GLuint shaderProgram);
    bool CheckHit(glm::vec3 shotStart, glm::vec3 shotEnd);
    bool IsAlive() const { return alive; }
    glm::vec3 GetPosition() const { return position; }

private:
    Level* level;
    glm::vec3 position;
    GLuint VAO;
    bool alive;
    float speed = 1.0f;
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
    static constexpr float SIZE = 1.0f;
    bool checkCollision(glm::vec3 newPosition);
};

#endif