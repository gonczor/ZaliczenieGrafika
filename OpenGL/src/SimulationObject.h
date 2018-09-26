#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class SimulationObject
{
public:
	SimulationObject(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color);

	virtual void draw() = 0;

	const glm::mat4& getObjectModel() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getDirection() const;
	const glm::vec3& getColor() const;

	void setPosition(const glm::vec3& position);
	void setDirection(const glm::vec3 &direction);
	void setColor(const glm::vec3& color);

protected:
	glm::vec3 m_color;
	glm::vec3 m_direction;
	glm::vec3 m_position;
	glm::mat4 m_objectModelToWorldMatrix;
};