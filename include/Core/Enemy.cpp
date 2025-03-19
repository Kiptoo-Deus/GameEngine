#include "Enemy.h"
#include <iostream>

Enemy::Enemy(glm::vec3 position) : position(position), VAO(0), alive(true) {}

void Enemy::Init(GLuint sharedVAO) {
    VAO = sharedVAO; // Share vertex data with main cube
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

    // Simple ray-AABB intersection
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