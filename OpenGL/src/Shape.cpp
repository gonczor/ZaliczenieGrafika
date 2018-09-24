#include "Shape.h"
#include <glm/glm.hpp>


Shape::Shape(GLuint size)
	:m_size(size)
{}

Shape::~Shape()
{}

const std::vector<Vertex>& Shape::getVertexBufferData() const
{
	return m_vertecies;
}

const std::vector<GLushort>& Shape::getIndexBufferData() const
{
	return m_indicies;
}

GLsizei Shape::getVertexBufferSize() const
{
	return static_cast<GLsizei>(m_vertecies.size());
}

GLsizei Shape::getIndexBufferSize() const
{
	return static_cast<GLsizei>(m_indicies.size());
}

Vertex::Vertex(glm::vec3 position)
	:position(position)
{}


