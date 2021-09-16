#version 330 core
in vec3 position;
in vec3 color;

out vec3 vertexColor;

uniform mat4 model;

void main()
{
    vertexColor = color;
    gl_Position = model * vec4(position, 1.0);
}