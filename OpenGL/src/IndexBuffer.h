#pragma once
#include <GL\glew.h>

class IndexBuffer
{
public:
	IndexBuffer(const GLvoid * data, GLsizei size);
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer(IndexBuffer&& other) = delete;
	~IndexBuffer();

public:
	void bind();
	void unBind();

private:
	GLuint m_renderObject = 0;
};

