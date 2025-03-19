#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Enemy {
public:
    Enemy(glm::vec3 position);
    void Init(GLuint sharedVAO); // Use shared vertex data from Renderer
    void Render(GLuint shaderProgram);
    bool CheckHit(glm::vec3 shotStart, glm::vec3 shotEnd);
    bool IsAlive() const { return alive; }

private:
    glm::vec3 position;
    GLuint VAO;
    bool alive;
    static constexpr float SIZE = 1.0f; // Same size as main cube
};

#endif