#pragma once
#include "Shape.h"

class SphereMesh :public Shape
{
public:
	SphereMesh(GLuint rings, GLuint sectors, GLfloat radius);
	~SphereMesh();
	void generate();

private:
	GLfloat map(GLfloat value, GLfloat low1, GLfloat max1, GLfloat low2, GLfloat max2);

	void addIndicies();

	void addVertecies();
	
private:
	GLuint m_sectors;
	GLfloat m_radius;
};

