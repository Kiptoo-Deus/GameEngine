#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "Shader.h"
#include "Camera.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Init(Camera* cam);
    void Render();
    void Shutdown();

private:
    GLuint VAO, VBO;
    Shader* shader;
    Camera* camera;
};

#endif