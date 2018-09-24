#include "SimulationObject.h"

#include<iostream>>
SimulationObject::SimulationObject(const glm::vec3& position) :
	m_position(position), 
	m_objectModelToWorldMatrix(1.0f)
{
	m_objectModelToWorldMatrix = glm::translate(m_objectModelToWorldMatrix, position);
}

const glm::mat4& SimulationObject::getObjectModel() const
{
	return m_objectModelToWorldMatrix;
}
