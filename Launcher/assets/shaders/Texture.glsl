#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTexCoords;

out vec2 texCoords;
out vec4 vColour;

// uniform mat4 MVP;

void main()
{
    vColour = vertexColour;
    // gl_Position = MVP * vec4(vertexPosition, 1.0);
    gl_Position = vec4(vertexPosition , 1.0);
    texCoords = vertexTexCoords;
}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoords;
in vec4 vColour;

uniform sampler2D texture_;
uniform float u_tilingFactor;
uniform vec4 u_Color;

void main()
{
    // color = texture(texture_, texCoords * u_tilingFactor).rgba * u_Color;
    color = vColour;
}