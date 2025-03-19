#include "Weapon.h"
#include <iostream>

Weapon::Weapon(Camera* cam) : camera(cam), lineShader(nullptr), lineVAO(0), lineVBO(0),
isShooting(false), shotTimer(0.0f) {}

void Weapon::Init() {
    // Simple shader for drawing lines
    lineShader = new Shader(
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/line_vertex.glsl",
        "C:/Users/JOEL/Documents/GitHub/GameEngine/GameEngine/shaders/line_fragment.glsl"
    );

    // Check if shader program linked successfully
    GLint success;
    glGetProgramiv(lineShader->GetProgram(), GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(lineShader->GetProgram(), 512, nullptr, infoLog);
        std::cout << "ERROR: Line shader program linking failed: " << infoLog << std::endl;
    }
    else {
        std::cout << "Line shader program linked successfully" << std::endl;
    }

    // Line vertices (will be updated dynamically)
    float lineVertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Start
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f  // End
    };

    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Weapon::Update(float deltaTime) {
    if (isShooting) {
        shotTimer -= deltaTime;
        if (shotTimer <= 0.0f) {
            isShooting = false;
        }
    }
}

void Weapon::Render() {
    if (isShooting) {
        std::cout << "Rendering shot, timer: " << shotTimer << std::endl;
        lineShader->Use();

        glm::mat4 model = glm::mat4(1.0f); // Add model matrix for consistency
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix(800.0f, 600.0f);

        glUniformMatrix4fv(glGetUniformLocation(lineShader->GetProgram(), "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lineShader->GetProgram(), "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lineShader->GetProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);

        float lineVertices[] = {
            shotStart.x, shotStart.y, shotStart.z, 1.0f, 1.0f, 1.0f,
            shotEnd.x, shotEnd.y, shotEnd.z, 1.0f, 1.0f, 1.0f
        };
        glBindVertexArray(lineVAO);
        glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(lineVertices), lineVertices);

        glDisable(GL_DEPTH_TEST); // Disable depth test for the line
        glDrawArrays(GL_LINES, 0, 2);
        glEnable(GL_DEPTH_TEST); // Re-enable depth test for other rendering
        glBindVertexArray(0);
    }
}

void Weapon::Shoot() {
    if (!isShooting) {
        isShooting = true;
        shotTimer = 0.2f;
        shotStart = camera->position;
        shotEnd = camera->position + camera->front * 10.0f;
        std::cout << "Shooting! Start: (" << shotStart.x << ", " << shotStart.y << ", " << shotStart.z
            << ") End: (" << shotEnd.x << ", " << shotEnd.y << ", " << shotEnd.z << ")" << std::endl;
    }
}