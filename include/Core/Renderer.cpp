#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : VAO(0), VBO(0), shader(nullptr) {}

Renderer::~Renderer() {
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::Init() {
    // I used an absolute path for my PC (change to your system's correct path)
    shader = new Shader("C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/vertex_shader.glsl",
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/fragment_shader.glsl");


    // Define triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate VAO & VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO & copy vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attributes (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::Render() {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (shader) {
        shader->Use(); // Ensure shader is applied
    }
    else {
        std::cerr << "ERROR: Shader is NULL in Render()" << std::endl;
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

