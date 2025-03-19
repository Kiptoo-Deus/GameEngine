#include "Enemy.h"
#include "GameEngine.h"
#include <iostream>

Enemy::Enemy(glm::vec3 position) : position(position), alive(true), level(nullptr), state(State::WALKING), attackTimer(0.0f), VAO(0) {}

void Enemy::Init(GLuint vao, Level* lvl) {
    VAO = vao;
    level = lvl;
}

void Enemy::Update(float deltaTime, const glm::vec3& playerPos, GameEngine* game) {
    if (!alive) return;

    float distanceToPlayer = glm::distance(playerPos, position);
    state = (distanceToPlayer < chaseDistance) ? State::RUNNING : State::WALKING;
    speed = (state == State::RUNNING) ? runSpeed : walkSpeed;

    direction = glm::normalize(playerPos - position);
    glm::vec3 newPosition = position + direction * speed * deltaTime;

    if (!checkCollision(newPosition)) {
        position = newPosition;
    }

    attackTimer -= deltaTime;
    if (distanceToPlayer < attackDistance && attackTimer <= 0.0f) {
        game->TakeDamage(damage);
        attackTimer = attackCooldown;
        std::cout << "Player hit! Health: " << game->GetHealth() << std::endl;
    }
}

void Enemy::Render(GLuint shaderProgram) {
    if (!alive) return;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

bool Enemy::checkCollision(const glm::vec3& newPosition) {
    if (level && level->CheckCollision(newPosition, size)) return true;
    return false;
}

bool Enemy::CheckHit(const glm::vec3& rayOrigin, const glm::vec3& rayDir) {
    // Simple bounding box check
    glm::vec3 min = position - glm::vec3(size);
    glm::vec3 max = position + glm::vec3(size);
    float tmin = (min.x - rayOrigin.x) / rayDir.x;
    float tmax = (max.x - rayOrigin.x) / rayDir.x;
    if (tmin > tmax) std::swap(tmin, tmax);
    float tymin = (min.y - rayOrigin.y) / rayDir.y;
    float tymax = (max.y - rayOrigin.y) / rayDir.y;
    if (tymin > tymax) std::swap(tymin, tymax);
    if ((tmin > tymax) || (tymin > tmax)) return false;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;
    float tzmin = (min.z - rayOrigin.z) / rayDir.z;
    float tzmax = (max.z - rayOrigin.z) / rayDir.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    if (tzmin > tmin) tmin = tzmin;
    if (tmax < 0) return false; // Behind camera
    alive = false; // Kill enemy on hit
    return true;
}