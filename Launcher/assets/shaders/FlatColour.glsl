// Flat colour shader

#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;

out vec3 vPos;
uniform mat4 model;

void main()
{
    gl_Position = model * vec4(vertexPosition, 1.0);
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