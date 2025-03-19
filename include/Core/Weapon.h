#ifndef WEAPON_H
#define WEAPON_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h" 

class Weapon {
public:
    Weapon(Camera* cam, Renderer* renderer); 
    void Init();
    void Update(float deltaTime);
    void Render();
    void Shoot();

private:
    Renderer* renderer; 
    Camera* camera;
    Shader* lineShader;
    GLuint lineVAO, lineVBO;
    glm::vec3 shotStart, shotEnd;
    bool isShooting;
    float shotTimer;
};

#endif