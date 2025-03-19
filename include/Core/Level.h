#ifndef LEVEL_H
#define LEVEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Level {
public:
    Level();
    void Init(GLuint vao);
    void Render(GLuint shaderProgram);
    bool CheckCollision(const glm::vec3& position, float size = 0.5f);

private:
    struct Wall {
        glm::vec3 position;
        glm::vec3 scale;
    };
    std::vector<Wall> walls;
    GLuint VAO; 
};

#endif