#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_ViewProjection;
out vec2 TexCoord;

void main() {
    TexCoord = vec2(a_TexCoord.x, a_TexCoord.y);
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core

out vec4 a_Color;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    a_Color = texture(texture1, TexCoord);
}