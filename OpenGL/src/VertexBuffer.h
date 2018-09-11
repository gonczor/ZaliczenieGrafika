#pragma once
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer(const GLvoid * data, GLsizei size);
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer(VertexBuffer&& other) = delete;
	~VertexBuffer();

public:
	void bind();
	void unBind();

private:
	GLuint m_renderObject = 0;	
};

