#include "SimulationObject.h"

#include<iostream>>
SimulationObject::SimulationObject(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color) :
	m_position(position),
	m_direction(direction),
	m_color(color),
	m_objectModelToWorldMatrix(1.0f)
{
	m_objectModelToWorldMatrix = glm::translate(m_objectModelToWorldMatrix, position);
}

const glm::mat4& SimulationObject::getObjectModel() const
{
	return m_objectModelToWorldMatrix;
}

const glm::vec3& SimulationObject::getPosition() const
{
	return m_position;
}

const glm::vec3& SimulationObject::getDirection() const
{
	return m_direction;
}

const glm::vec3& SimulationObject::getColor() const
{
	return m_color;
}

void SimulationObject::setPosition(const glm::vec3& position)
{
	m_position = position;
}

void SimulationObject::setDirection(const glm::vec3& direction)
{
	m_direction = direction;
}

void SimulationObject::setColor(const glm::vec3& color)
{
	m_color = color;
}
