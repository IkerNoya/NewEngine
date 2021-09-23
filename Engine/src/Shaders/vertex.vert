#version 330 core
in vec3 position;
in vec3 color;

out vec3 vertexColor;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main()
{
    vertexColor = color;
    gl_Position = projection * view * model * vec4(position, 1.0);
}