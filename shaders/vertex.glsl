#version 410 core

in vec3 inPosition;
in vec3 inColor;
in vec3 inNormal;
in vec2 inTexCoords;
out vec3 passColor;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1.0);
    passColor = inColor;
}