#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Tangent;
layout(location = 4) in vec3 a_Bitangent;

out vec2 f_TexCoord;
uniform mat4 u_ViewProjection;

void main() {
    f_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
}


#type fragment
#version 330 core

in vec2 f_TexCoord;
out vec4 o_Color;
uniform sampler2D albedoMap;

void main() {
    o_Color = texture(albedoMap, f_TexCoord) * 0.5f;
}