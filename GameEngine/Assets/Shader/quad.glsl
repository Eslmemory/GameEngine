#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
out vec4 f_Color;
out vec2 f_TexCoord;
out float f_TexIndex;

uniform mat4 a_ViewProjection;

void main() {
    f_Color = a_Color;
    f_TexCoord = a_TexCoord;
    f_TexIndex = a_TexIndex;
    gl_Position = a_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core

in vec4 f_Color;
in vec2 f_TexCoord;
in float f_TexIndex;
out vec4 Color;

uniform sampler2D u_Textures[32];

void main() {
    Color = texture(u_Textures[int(f_TexIndex)], f_TexCoord) * f_Color;
}