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

	virtual ~Shape();
	virtual void generate() = 0;
	
	virtual const std::vector<Vertex>& getVertexBufferData() const;
	virtual const std::vector<GLushort>& getIndexBufferData() const;

	virtual GLsizei getVertexBufferSize() const;
	virtual GLsizei getIndexBufferSize() const;
	

protected:
	GLsizei m_size;
	std::vector<Vertex> m_vertecies;
	std::vector<GLushort> m_indicies;
	std::vector<glm::vec2> m_texcords;

};

