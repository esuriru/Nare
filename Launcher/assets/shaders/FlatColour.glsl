// Flat colour shader

#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;

out vec3 vPos;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    vPos = vertexPosition;
}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vPos;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
    // color = vec4(1, 0, 0, 1);
}