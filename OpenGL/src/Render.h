#pragma once
#include "SphereMesh.h"
#include "Program.h"
#include "Particle.h"

class Render
{
public:
	explicit Render(GLuint amount, const SphereMesh& sphereMesh);
	~Render();
	void pushDataToBuffer();

	void paintSpheres();

private:
	GLsizei m_vertexBufferSize = 0;
	GLsizei m_indexBufferSize = 0;
	
	std::vector<Vertex> m_vertexBufferData;
	std::vector<GLushort> m_indexBufferData;

	GLuint m_amountObjects = 0;
	GLuint m_bufferArrayID = 0;
	GLuint m_sphereID = 0;

	std::vector<Particle> particles;

	ShaderProgram shader;
};

