#type vertex
#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;


// uniform mat4 MVP;

out vec2 v_tex_coords;
out vec3 v_normal;

void main()
{
    v_tex_coords = vertexUV;
    v_normal = vertexNormal;
    gl_Position = vec4(vertexPosition , 1.0);
}

#type pixel
#version 330 core

layout(location = 0) out vec4 color;

const int MAX_LIGHTS = 20;

struct Light
{
    vec4 position_camera_space;
    vec4 colour;
    vec4 direction_camera_space;

    int type;

    float power;

    float cos_cutoff;
    float cos_inner;

    float constant;
    float linear;
    float quadratic;
}

layout (std140) uniform LightBlock
{
    Light lights[MAX_LIGHTS];
}

in vec2 v_tex_coords;
in vec3 v_normal;

uniform sampler2D texture_;
uniform sampler2D u_Textures[32]; // FOR NOW, MAXIMUM 32 TEXTURES.

void main()
{
    // Allegedly NVIDIA cards can only handle this code.
    // color = texture(u_Textures[int(vTexIndex)], texCoords * v_tilingFactor)  * v_Colour;
    // vec4 texColor = v_Colour;

    // Have to do this because AMD cards cannot handle the above code.
    // switch(int(vTexIndex))
    // {
    //     case 0: texColor *= texture(u_Textures[0], texCoords * v_tilingFactor); break;
    //     case 1: texColor *= texture(u_Textures[1], texCoords * v_tilingFactor); break;
    //     case 2: texColor *= texture(u_Textures[2], texCoords * v_tilingFactor); break;
    //     case 3: texColor *= texture(u_Textures[3], texCoords * v_tilingFactor); break;
    //     case 4: texColor *= texture(u_Textures[4], texCoords * v_tilingFactor); break;
    //     case 5: texColor *= texture(u_Textures[5], texCoords * v_tilingFactor); break;
    //     case 6: texColor *= texture(u_Textures[6], texCoords * v_tilingFactor); break;
    //     case 7: texColor *= texture(u_Textures[7], texCoords * v_tilingFactor); break;
    //     case 8: texColor *= texture(u_Textures[8], texCoords * v_tilingFactor); break;
    //     case 9: texColor *= texture(u_Textures[9], texCoords * v_tilingFactor); break;
    //     case 10:texColor *= texture(u_Textures[10], texCoords * v_tilingFactor); break;
    //     case 11:texColor *= texture(u_Textures[11], texCoords * v_tilingFactor); break;
    //     case 12:texColor *= texture(u_Textures[12], texCoords * v_tilingFactor); break;
    //     case 13:texColor *= texture(u_Textures[13], texCoords * v_tilingFactor); break;
    //     case 14:texColor *= texture(u_Textures[14], texCoords * v_tilingFactor); break;
    //     case 15:texColor *= texture(u_Textures[15], texCoords * v_tilingFactor); break;
    //     case 16:texColor *= texture(u_Textures[16], texCoords * v_tilingFactor); break;
    //     case 17:texColor *= texture(u_Textures[17], texCoords * v_tilingFactor); break;
    //     case 18:texColor *= texture(u_Textures[18], texCoords * v_tilingFactor); break;
    //     case 19:texColor *= texture(u_Textures[19], texCoords * v_tilingFactor); break;
    //     case 20:texColor *= texture(u_Textures[20], texCoords * v_tilingFactor); break;
    //     case 21:texColor *= texture(u_Textures[21], texCoords * v_tilingFactor); break;
    //     case 22:texColor *= texture(u_Textures[22], texCoords * v_tilingFactor); break;
    //     case 23:texColor *= texture(u_Textures[23], texCoords * v_tilingFactor); break;
    //     case 24:texColor *= texture(u_Textures[24], texCoords * v_tilingFactor); break;
    //     case 25:texColor *= texture(u_Textures[25], texCoords * v_tilingFactor); break;
    //     case 26:texColor *= texture(u_Textures[26], texCoords * v_tilingFactor); break;
    //     case 27:texColor *= texture(u_Textures[27], texCoords * v_tilingFactor); break;
    //     case 28:texColor *= texture(u_Textures[28], texCoords * v_tilingFactor); break;
    //     case 29:texColor *= texture(u_Textures[29], texCoords * v_tilingFactor); break;
    //     case 30:texColor *= texture(u_Textures[30], texCoords * v_tilingFactor); break;
    //     case 31:texColor *= texture(u_Textures[31], texCoords * v_tilingFactor); break;
    // }
    // color = texColor;

    color = texture(texture_, v_tex_coords).rgba;
}