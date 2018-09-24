#version 330 core

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 MVP;


void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	v_TexCoord = texCoord;
};

