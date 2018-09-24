#version 330 core

out vec4 color;

in vec2 v_TexCoord;


uniform vec3 u_Color;
uniform sampler2D u_Tex;


void main()
{
	vec4 texColor = texture(u_Tex, v_TexCoord);
	color = texColor * vec4(u_Color, 1.0f);
};