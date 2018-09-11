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
		os << "x: " << obj.position.x << " y: " << obj.position.y << " z: " << obj.position.z << '\n';
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

	friend class Window;
	

protected:
	GLuint m_size;
	std::vector<Vertex> m_vertecies;
	std::vector<GLushort> m_indicies;

};

