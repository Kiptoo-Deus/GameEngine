#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor; // Add this

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Color = aColor * objectColor; // Multiply vertex color with uniform
}