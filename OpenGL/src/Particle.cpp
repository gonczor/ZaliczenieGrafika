#include "Particle.h"

#include <random>

Particle::Particle(const glm::vec3& position, const glm::vec3& direction) :
	SimulationObject(position), m_direction(direction)
{
	
}

Particle::~Particle()
{
	
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
	//if (m_position.x >= 10.0f || m_position.y >= 10.0f && m_position.z >= 10.0f || m_position.x >= -10.0f || m_position.y >= -10.0f && m_position.z >= -10.0f)
	//{
	//	m_direction *= -1;
	//}
	m_position += m_direction;
	m_objectModelToWorldMatrix = glm::translate(m_objectModelToWorldMatrix, m_direction);
}

bool Particle::detectColision()
{
	return false;
}
