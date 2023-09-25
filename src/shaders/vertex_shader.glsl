#version 330 core

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec3 vertexColorIn;
uniform mat4 camera;

out vec3 vertexColor;

void main()
{
    gl_Position = camera * vertexPosition;
    vertexColor = vertexColorIn;
}
