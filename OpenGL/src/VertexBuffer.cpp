#include "VertexBuffer.h"
#include <iostream>


VertexBuffer::VertexBuffer(const GLvoid * data, GLsizei size)
{
	glGenBuffers(1, &m_renderObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderObject);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	std::cout << "Delete buffer\n";
	glDeleteBuffers(1, &m_renderObject);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderObject);
}

void VertexBuffer::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);
}
