#pragma once
#include "SimulationObject.h"
#include <GL/glew.h>

class Particle :
	public SimulationObject
{
public:
	Particle(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);
	virtual ~Particle();

	virtual void draw() override;

	static GLfloat GenerateFloatNumber(GLfloat rangeMin, GLfloat rangeMax);
	static GLfloat GenerateIntNumber(GLint rangeMin, GLint rangeMax);

private:
	void move();

private:
	unsigned int m_countOfMoves = 0;
};

