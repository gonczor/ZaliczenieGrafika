#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void mouseUpdate(const glm::vec2& newMousePoint);
	glm::mat4 getWorldToViewMatrix() const;


private:
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec2 oldMousePosition;
	float speed;

	const glm::vec3 UP;
};

