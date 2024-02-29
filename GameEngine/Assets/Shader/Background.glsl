#type vertex

#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 u_ViewProjection;

void main()
{
	pos = aPos;
	gl_Position = u_ViewProjection * model * vec4(aPos, 1.0);
}


#type fragment

#version 330 core

in vec3 pos;
out vec4 FragColor;

uniform samplerCube environmentMap;

void main()
{
	vec3 color = texture(environmentMap, pos).rgb;
	FragColor = vec4(color, 1.0);
}