#include "Particle.h"

#include <iostream>
#include <random>

Particle::Particle(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color) :
	SimulationObject(position, direction, color)
{}

Particle::~Particle()
{}

void Particle::draw()
{
	move();
}

GLfloat Particle::GenerateFloatNumber(GLfloat rangeMin, GLfloat rangeMax)
{
	static std::random_device randomDevice{};
	static std::mt19937 randomEngineGenerator(randomDevice());
	std::uniform_real_distribution<GLfloat> dist(rangeMin, rangeMax);

	return dist(randomEngineGenerator);
}

GLfloat Particle::GenerateIntNumber(GLint rangeMin, GLint rangeMax)
{
	static std::random_device randomDevice{};
	static std::mt19937 randomEngineGenerator(randomDevice());
	std::uniform_int_distribution<GLint> dist(rangeMin, rangeMax);

	return static_cast<GLfloat>(dist(randomEngineGenerator));
}

void Particle::move()
{
	m_position += m_direction;
	m_objectModelToWorldMatrix = glm::translate(m_objectModelToWorldMatrix, m_direction);
}
