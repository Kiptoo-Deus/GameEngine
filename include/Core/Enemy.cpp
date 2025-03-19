#include "Enemy.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Enemy::Enemy(glm::vec3 position) : position(position), VAO(0), alive(true), level(nullptr) {}

void Enemy::Init(GLuint sharedVAO, Level* lvl) {
    VAO = sharedVAO;
    level = lvl;
}

void Enemy::Update(float deltaTime, const glm::vec3& playerPos) { 
    if (!alive) return;

    // Move toward player
    direction = glm::normalize(playerPos - position);
    glm::vec3 newPosition = position + direction * speed * deltaTime;

    if (newPosition.x + SIZE / 2 > 5.0f || newPosition.x - SIZE / 2 < -5.0f) {
        direction.x = -direction.x;
        newPosition.x = glm::clamp(newPosition.x, -4.5f, 4.5f);
    }
    if (newPosition.z + SIZE / 2 > 5.0f || newPosition.z - SIZE / 2 < -5.0f) {
        direction.z = -direction.z;
        newPosition.z = glm::clamp(newPosition.z, -4.5f, 4.5f);
    }
    if (!checkCollision(newPosition)) {
        position = newPosition;
    }
    else {
        direction = -direction;
    }
}

bool Enemy::checkCollision(glm::vec3 newPosition) {
    glm::vec3 cubeMin(-0.5f, -0.5f, -0.5f);
    glm::vec3 cubeMax(0.5f, 0.5f, 0.5f);
    glm::vec3 enemyMin = newPosition - glm::vec3(SIZE / 2);
    glm::vec3 enemyMax = newPosition + glm::vec3(SIZE / 2);

    if (enemyMin.x < cubeMax.x && enemyMax.x > cubeMin.x &&
        enemyMin.y < cubeMax.y && enemyMax.y > cubeMin.y &&
        enemyMin.z < cubeMax.z && enemyMax.z > cubeMin.z) {
        return true;
    }

    if (newPosition.y - SIZE / 2 < -0.5f) return true;

    if (level && level->CheckCollision(newPosition, SIZE / 2)) return true;

    return false;
}

void Enemy::Render(GLuint shaderProgram) {
    if (!alive) return;

    glUseProgram(shaderProgram);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

bool Enemy::CheckHit(glm::vec3 shotStart, glm::vec3 shotEnd) {
    if (!alive) return false;

    glm::vec3 minBounds = position - glm::vec3(SIZE / 2);
    glm::vec3 maxBounds = position + glm::vec3(SIZE / 2);

    glm::vec3 dir = glm::normalize(shotEnd - shotStart);
    float tmin = 0.0f;
    float tmax = glm::distance(shotStart, shotEnd);

    for (int i = 0; i < 3; i++) {
        if (std::abs(dir[i]) < 0.0001f) {
            if (shotStart[i] < minBounds[i] || shotStart[i] > maxBounds[i]) return false;
        }
        else {
            float t1 = (minBounds[i] - shotStart[i]) / dir[i];
            float t2 = (maxBounds[i] - shotStart[i]) / dir[i];
            if (t1 > t2) std::swap(t1, t2);
            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);
            if (tmin > tmax) return false;
        }
    }

    if (tmin <= tmax && tmin >= 0.0f) {
        alive = false;
        return true;
    }
    return false;
}