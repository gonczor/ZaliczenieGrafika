#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const GLvoid * data, GLsizei size)
{
	glGenBuffers(1, &m_renderObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_renderObject);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderObject);
}

void IndexBuffer::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_ZERO);
}
