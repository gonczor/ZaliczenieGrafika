#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class SimulationObject
{
public:
	SimulationObject(const glm::vec3& position);
	virtual void move() = 0;
	virtual bool detectColision() = 0;

	const glm::mat4& getObjectModel() const;

protected:
	glm::vec3 m_position;
	glm::mat4 m_objectModelToWorldMatrix;
};