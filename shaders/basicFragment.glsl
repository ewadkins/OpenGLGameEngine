#version 410 core

in vec3 passColor;
out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = vec4(passColor, 1.0);
}