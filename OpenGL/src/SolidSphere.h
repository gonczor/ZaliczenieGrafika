#pragma once
#include "Shape.h"

class SolidSphere :public Shape
{
public:
	SolidSphere(GLuint size, GLfloat radius);
	~SolidSphere();
	void generate();


private:
	GLfloat map(GLfloat value, GLfloat low1, GLfloat max1, GLfloat low2, GLfloat max2);

private:
	GLuint m_rings;
	GLfloat m_radius;
};

