#include "GameEngine.h"
#include <iostream>
#include <GL/glew.h>

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
    Shutdown();
}

bool GameEngine::Init() {
    std::cout << "Initializing Game Engine..." << std::endl;

    // Initialize Window
    window = new Window("Game Engine 3D", 800, 600);
    if (!window->Init()) {
        return false;
    }

    // OpenGL Setup
    glViewport(0, 0, 800, 600);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark gray background

    return true;
}

void GameEngine::Run() {
    std::cout << "Running Game Engine..." << std::endl;

    // Triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Bottom Left
         0.5f, -0.5f, 0.0f,  // Bottom Right
         0.0f,  0.5f, 0.0f   // Top Middle
    };

    // Generate OpenGL buffers
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (true) {
        window->PollEvents();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window->SwapBuffers();
    }
}

void GameEngine::Shutdown() {
    std::cout << "Shutting down Game Engine..." << std::endl;
}
