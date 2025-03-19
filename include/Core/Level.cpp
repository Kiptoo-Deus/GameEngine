#include "Level.h"
#include <glm/gtc/matrix_transform.hpp>

Level::Level() {}

void Level::Init(GLuint vao) {
    VAO = vao;
    walls.push_back({ glm::vec3(0.0f, 0.5f, 5.0f), glm::vec3(10.0f, 1.0f, 0.1f) }); // North
    walls.push_back({ glm::vec3(0.0f, 0.5f, -5.0f), glm::vec3(10.0f, 1.0f, 0.1f) }); // South
    walls.push_back({ glm::vec3(5.0f, 0.5f, 0.0f), glm::vec3(0.1f, 1.0f, 10.0f) }); // East
    walls.push_back({ glm::vec3(-5.0f, 0.5f, 0.0f), glm::vec3(0.1f, 1.0f, 10.0f) }); // West
}

void Level::Render(GLuint shaderProgram) {
    glm::mat4 floorModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
    floorModel = glm::scale(floorModel, glm::vec3(10.0f, 0.1f, 10.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &floorModel[0][0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    for (const Wall& wall : walls) {
        glm::mat4 wallModel = glm::translate(glm::mat4(1.0f), wall.position);
        wallModel = glm::scale(wallModel, wall.scale);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &wallModel[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}

bool Level::CheckCollision(const glm::vec3& position, float radius) { 
    // Check floor (ensure player doesn’t fall through)
    if (position.y - radius < -0.5f) return true;

    for (const Wall& wall : walls) {
        glm::vec3 minBounds = wall.position - wall.scale * 0.5f;
        glm::vec3 maxBounds = wall.position + wall.scale * 0.5f;
        glm::vec3 closestPoint = glm::clamp(position, minBounds, maxBounds);
        float distance = glm::distance(position, closestPoint);
        if (distance < radius) return true;
    }
    return false;
}