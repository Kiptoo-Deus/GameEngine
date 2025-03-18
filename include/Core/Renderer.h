#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Init();
    void Render();

private:
    GLuint VAO, VBO;
    Shader* shader;
};

#endif // RENDERER_H
