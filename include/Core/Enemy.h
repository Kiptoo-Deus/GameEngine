#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Level.h"

class GameEngine;

class Enemy {
public:
    enum class State { WALKING, RUNNING };
    Enemy(glm::vec3 position);
    void Init(GLuint vao, Level* lvl = nullptr);
    void Update(float deltaTime, const glm::vec3& playerPos, GameEngine* game);
    void Render(GLuint shaderProgram);
    bool CheckHit(const glm::vec3& rayOrigin, const glm::vec3& rayDir); // Add this
    bool IsAlive() const { return alive; }
    glm::vec3 GetPosition() const { return position; }

private:
    bool checkCollision(const glm::vec3& newPosition); // Match declaration

    glm::vec3 position;
    glm::vec3 direction;
    float speed;
    float walkSpeed = 1.0f;
    float runSpeed = 2.5f;
    float chaseDistance = 5.0f;
    bool alive;
    Level* level;
    State state;
    float attackDistance = 1.0f;
    float attackCooldown = 1.0f;
    float attackTimer = 0.0f;
    float damage = 10.0f;
    GLuint VAO;
    float size = 0.5f; // Add this for collision/hit detection
};

#endif