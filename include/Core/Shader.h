#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use();
    GLuint GetProgram() const { return shaderProgram; }

private:
    GLuint shaderProgram;
    GLuint LoadShader(const std::string& path, GLenum type);
};

#endif // SHADER_H