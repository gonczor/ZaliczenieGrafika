#include "Shape.h"
#include <glm/glm.hpp>




Shape::Shape(GLuint size)
	:m_size(size)
{
	
}

Shape::~Shape()
{
}

Vertex::Vertex(glm::vec3 position)
	:position(position)
{}
