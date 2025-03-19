#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));
    void SetLevel(Level* lvl) { level = lvl; }
    void ProcessKeyboard(float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float width, float height);

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
private:
    Level* level;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    float fov = 45.0f;
    float playerRadius = 0.2f; // Small radius for player collision

    void updateCameraVectors();
    bool checkCollision(glm::vec3 newPosition);
};

#endif