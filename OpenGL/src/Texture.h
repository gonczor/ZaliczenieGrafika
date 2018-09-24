#pragma once
#include <gl/glew.h>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& imagepath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind();

private:
	int m_width = 0;
	int m_height = 0;
	int m_nrChannels = 0;
	unsigned char* m_data = nullptr;
	GLuint m_renderObjectID = 0;
	std::string m_imagepath;
};

