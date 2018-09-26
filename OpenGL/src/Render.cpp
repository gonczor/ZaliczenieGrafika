#include "Render.h"
#include "glm/gtc/matrix_transform.hpp"
#include "stdlib.h"


Render::Render(GLuint amount, const SphereMesh & sphereMesh) :
	m_amountObjects(amount),
	m_vertexBufferData(sphereMesh.getVertexBufferData()),
	m_indexBufferData(sphereMesh.getIndexBufferData()),
	m_vertexBufferSize(sphereMesh.getVertexBufferSize() * sizeof(m_vertexBufferData[0])),
	m_indexBufferSize(sphereMesh.getIndexBufferSize() * sizeof(m_indexBufferData[0])),
	particleShader(ShaderProgram(
		"resources/shaders/vertex_shader.glsl",
		"resources/shaders/fragment_shader.glsl"))
{
	elements.emplace_back(std::make_unique<Particle>(
		glm::vec3(10.0f, 1.0f, 1.0f), 
		glm::vec3(-0.1f, 0.0f, 0.0f), 
		glm::vec3(1.0f, 0.0f, 0.0f)));

	elements.emplace_back(std::make_unique<Particle>(
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(+0.1f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)));
}

Render::~Render()
{
	glDeleteBuffers(1, &m_bufferArrayID);
	glDeleteBuffers(1, &m_sphereID);
}

void Render::pushDataToBuffer()
{
	glGenBuffers(1, &m_bufferArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferArrayID);
	glBufferData(GL_ARRAY_BUFFER, m_vertexBufferSize + m_indexBufferSize, 0, GL_STATIC_DRAW);

	GLsizeiptr offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, m_vertexBufferSize, &m_vertexBufferData[0]);
	offset += m_vertexBufferSize;
	std::cout << offset << std::endl;
	glBufferSubData(GL_ARRAY_BUFFER, offset, m_indexBufferSize, &m_indexBufferData[0]);
	offset += m_indexBufferSize;

	glGenVertexArrays(1, &m_sphereID);
	glBindVertexArray(m_sphereID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferArrayID);
	glVertexAttribPointer(
		0, 
		3, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex), 
		static_cast<const void*>(0)
	);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferArrayID);

	particleShader.setUniform("u_Tex", 0);
}


GLboolean Render::detectColisions(const SimulationObject* first, const SimulationObject* second) const
{
	static GLfloat radius = 1.5f;
	glm::vec3 firstvec = first->getPosition();
	glm::vec3 secondvec = second->getPosition();

	bool colisionX = checkColisionCordinates(firstvec.x, secondvec.x, radius);
	bool colisionY = checkColisionCordinates(firstvec.y, secondvec.y, radius);
	bool colisionZ = checkColisionCordinates(firstvec.y, secondvec.y, radius);

	return colisionX && colisionY && colisionZ;
}

GLboolean Render::checkColisionCordinates(const GLfloat& firstCordinate, const GLfloat& secondCordinate, const GLfloat& size) const
{
	GLboolean colision = firstCordinate + size >= secondCordinate &&
		secondCordinate + size >= firstCordinate;
	return colision;
}

void Render::doColisions()
{
	for (unsigned short sourceParticle = 0; sourceParticle < m_amountObjects; sourceParticle++)
	{
		for (unsigned short nextParticle = 0; nextParticle < m_amountObjects; nextParticle++)
		{
			if (detectColisions(elements[sourceParticle].get(), elements[nextParticle].get()) && nextParticle != sourceParticle)
			{
				std::cout << "Colision\n";
			}
		}
	}
}


void Render::drawElements()
{
	particleShader.use();
	glm::vec3 color(1.0f, 1.0f, 0.0f);
	for(unsigned short i = 0; i < m_amountObjects; ++i)
	{
		glm::mat4 object = elements[i]->getObjectModel();
		glm::mat4 MVP = Projection * View * object;
		particleShader.setUniform("MVP", MVP);
		particleShader.setUniform("u_Color", elements[i]->getColor());
		glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, (void*)m_vertexBufferSize);
		elements[i]->draw();
	}
	doColisions();
}






