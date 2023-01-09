#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

out vec3 vPos;
out vec2 texCoords;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
    vPos = vertexPosition;
    texCoords = vertexTexCoords;
}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoords;

uniform sampler2D texture_;
uniform float u_tilingFactor;
uniform vec4 u_Color;

void main()
{
    color = texture(texture_, texCoords * u_tilingFactor).rgba * u_Color;
}