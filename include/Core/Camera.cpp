#include "Camera.h"
#include <SDL2/SDL.h>

Camera::Camera(glm::vec3 position) : position(position), level(nullptr) {
    updateCameraVectors();
}
bool Camera::checkCollision(glm::vec3 newPosition) {
    glm::vec3 cubeMin(-0.5f, -0.5f, -0.5f);
    glm::vec3 cubeMax(0.5f, 0.5f, 0.5f);
    glm::vec3 closestPoint = glm::clamp(newPosition, cubeMin, cubeMax);
    float distance = glm::distance(newPosition, closestPoint);
    if (distance < playerRadius) return true;

    if (level && level->CheckCollision(newPosition, playerRadius)) return true;

    return false;
}
void Camera::ProcessKeyboard(float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    glm::vec3 newPosition = position;

    if (state[SDL_SCANCODE_W]) newPosition += front * velocity;
    if (state[SDL_SCANCODE_S]) newPosition -= front * velocity;
    if (state[SDL_SCANCODE_A]) newPosition -= right * velocity;
    if (state[SDL_SCANCODE_D]) newPosition += right * velocity;

    // Only update position if no collision
    if (!checkCollision(newPosition)) {
        position = newPosition;
    }
}

void Camera::ProcessMouse(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height) {
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}