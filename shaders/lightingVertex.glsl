#version 410 core

in vec3 inPosition;
in vec3 inColor;
in vec3 inNormal;
in vec3 inTexCoords;
out vec3 passPosition;
out vec3 passColor;
out vec3 passNormal;
out vec3 passTexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool modelViewProjectionEnabled;

void main()
{
    if (modelViewProjectionEnabled)
        gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 1.0);
    else
        gl_Position = vec4(inPosition, 1.0);
    passPosition = inPosition;
    passColor = inColor;
    passNormal = inNormal;
    passTexCoords = inTexCoords;
}