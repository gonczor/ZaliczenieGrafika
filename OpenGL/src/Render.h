#pragma once
#include "SphereMesh.h"
#include "Program.h"
#include "Particle.h"
#include <memory>

class Render
{
public:
	explicit Render(GLuint amount, const SphereMesh& sphereMesh);
	~Render();

	void pushDataToBuffer();
	void drawElements();
	void doColisions();

private:
	GLboolean detectColisions(const SimulationObject* first, const SimulationObject* second) const;
	GLboolean checkColisionCordinates(const GLfloat& first, const GLfloat& second, const GLfloat& size) const;

private:
	GLsizei m_vertexBufferSize = 0;
	GLsizei m_indexBufferSize = 0;
	
	std::vector<Vertex> m_vertexBufferData;
	std::vector<GLushort> m_indexBufferData;

	GLuint m_amountObjects = 0;
	GLuint m_bufferArrayID = 0;
	GLuint m_sphereID = 0;

	std::vector<std::unique_ptr<SimulationObject>> elements;

	ShaderProgram particleShader;

	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
};

