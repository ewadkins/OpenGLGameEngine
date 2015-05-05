#version 410 core

in vec3 passPosition;
in vec3 passColor;
in vec3 passNormal;
in vec3 passTexCoords;
out vec4 outColor;

void main()
{
    outColor = vec4(abs(passPosition), 1.0);
}