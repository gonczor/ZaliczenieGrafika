#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct Vertex
{
	Vertex(glm::vec3 position);
	glm::vec3 position;

	friend std::ostream& operator << (std::ostream &os, const Vertex &obj)
	{
		os << obj.position.x << " " << obj.position.y << " " << obj.position.z << '\n';
		return os;
	}
};

class Shape
{
public:
	Shape(GLuint size);
	Shape(const Shape& other) = delete;
	Shape(Shape&& other) = delete;

	virtual ~Shape();
	virtual void generate() = 0;
	

protected:
	GLuint m_size;
	std::vector<Vertex> m_vertecies;
	std::vector<GLushort> m_indicies;

};

