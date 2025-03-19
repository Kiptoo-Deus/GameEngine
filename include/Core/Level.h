#ifndef LEVEL_H
#define LEVEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Level {
public:
    Level();
    void Init(GLuint sharedVAO);
    void Render(GLuint shaderProgram);
    bool CheckCollision(glm::vec3 position, float radius);

private:
    GLuint VAO;
    struct Wall {
        glm::vec3 position;
        glm::vec3 scale; // For flat walls
    };
    std::vector<Wall> walls;
};

#endif