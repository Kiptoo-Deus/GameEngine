#include "Renderer.h"
#include <iostream>

#include "Renderer.h"
#include <iostream>

// Complete cube vertices (position + color)
float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Bottom-left
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Bottom-right
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Top-right
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Top-right
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, // Top-left
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Bottom-left

    // Back face
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

    // Left face
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

    // Right face
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

     // Top face
     -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
      0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
     -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

     // Bottom face
     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f
};

Renderer::Renderer() : VAO(0), VBO(0), shader(nullptr), camera(nullptr) {}

void Renderer::Init(Camera* cam) {
    camera = cam;
    shader = new Shader(
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/vertex_shader.glsl",
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/fragment_shader.glsl"
    );

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
}

void Renderer::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix(800.0f, 600.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices for a complete cube
    glBindVertexArray(0);

    RenderCrosshair();
}
void Renderer::RenderCrosshair() {
    glUseProgram(0); // Disable shader for immediate mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1); // 2D ortho projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); // White crosshair
    glBegin(GL_LINES);
    // Horizontal line
    glVertex2f(390.0f, 300.0f);
    glVertex2f(410.0f, 300.0f);
    // Vertical line
    glVertex2f(400.0f, 290.0f);
    glVertex2f(400.0f, 310.0f);
    glEnd();
}

Renderer::~Renderer() {
    Shutdown();
}


void Renderer::Shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
}