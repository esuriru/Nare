#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTexCoords;
layout(location = 3) in float vertexTexIndex;

out vec2 texCoords;
out vec4 v_Colour;
out float vTexIndex;

// uniform mat4 MVP;

void main()
{
    v_Colour = vertexColour;
    vTexIndex = vertexTexIndex;
    texCoords = vertexTexCoords;
    gl_Position = vec4(vertexPosition , 1.0);
    // gl_Position = MVP * vec4(vertexPosition, 1.0);
}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoords;
in vec4 v_Colour;
in float vTexIndex;

uniform sampler2D texture_;
uniform float u_tilingFactor;
uniform vec4 u_Color;
uniform sampler2D u_Textures[32]; // FOR NOW, MAXIMUM 32 TEXTURES.

void main()
{
    // TODO - u_TilingFactor
    // color = texture(texture_, texCoords * u_tilingFactor).rgba * u_Color;
    color = texture(u_Textures[int(vTexIndex)], texCoords)  * v_Colour;
}