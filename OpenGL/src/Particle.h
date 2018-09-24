#pragma once
#include "SimulationObject.h"
#include <GL/glew.h>

class Particle :
	public SimulationObject
{
public:
	Particle(const glm::vec3& position, const glm::vec3& direction);
	virtual void move() override;
	virtual bool detectColision() override;
	virtual ~Particle();

	static GLfloat GenerateFloatNumber(GLfloat rangeMin, GLfloat rangeMax);
	static GLfloat GenerateIntNumber(GLint rangeMin, GLint rangeMax);

private:
	glm::vec3 m_direction;
	unsigned int m_countOfMoves = 0;
};

