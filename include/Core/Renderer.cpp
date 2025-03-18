#include "Renderer.h"
#include <iostream>

// Vertex Data (Position + RGB)
float vertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Red
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Green
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Blue
};

// Constructor
Renderer::Renderer() : VAO(0), VBO(0), shader(nullptr) {}

// Destructor
Renderer::~Renderer() {
    Shutdown();
}

// Initialize Renderer
void Renderer::Init() {  
    // Load Shader Program
    shader = new Shader(
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/vertex_shader.glsl",
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/fragment_shader.glsl"
    );

    // Generate OpenGL Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Render Frame
void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    shader->Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

// Shutdown Cleanup
void Renderer::Shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
}
