#version 330 core

in layout(location = 0) vec2 position;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
};
