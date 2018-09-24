#include "Render.h"
#include "glm/gtc/matrix_transform.hpp"
#include "stdlib.h"


Render::Render(GLuint amount, const SphereMesh & sphereMesh) :
	m_amountObjects(amount),
	m_vertexBufferData(sphereMesh.getVertexBufferData()),
	m_indexBufferData(sphereMesh.getIndexBufferData()),
	m_vertexBufferSize(sphereMesh.getVertexBufferSize() * sizeof(m_vertexBufferData[0])),
	m_indexBufferSize(sphereMesh.getIndexBufferSize() * sizeof(m_indexBufferData[0])),
	shader(ShaderProgram(
		"resources/shaders/vertex_shader.glsl",
		"resources/shaders/fragment_shader.glsl"))
{
	for (int i = 0; i < m_amountObjects; ++i)
	{
		glm::vec3 position(
			Particle::GenerateFloatNumber(-1.0f, 1.0f),
			Particle::GenerateFloatNumber(-1.0f, 1.0f),
			Particle::GenerateFloatNumber(-1.0f, 1.0f)
		);

		glm::vec3 direction{
			Particle::GenerateIntNumber(-10, 10),
			Particle::GenerateIntNumber(-10, 10),
			Particle::GenerateIntNumber(-10, 10)
		};

		particles.emplace_back(position, direction);
	}
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

	shader.setUniform1i("u_Tex", 0);
}


void Render::paintSpheres()
{
	shader.use();
	glBindVertexArray(m_sphereID);
	static glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
	static glm::mat4 View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//glm::mat4 cubeModel1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, -0.5, 0.0));
	//glm::mat4 MVP = Projection * View * cubeModel1;
	//shader.setUniformMatrix4fv("MVP", MVP);
	//shader.setUniform3fv("u_Color", glm::vec3(1.0, 0.5, 0.0));
	//glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(m_vertexBufferSize));

	//glm::mat4 cubeModel2 = glm::translate(cubeModel1, glm::vec3(1.0, -1.0, 0.0));

	//MVP = Projection * View * cubeModel2;
	//shader.setUniformMatrix4fv("MVP", MVP);
	//shader.setUniform3fv("u_Color", glm::vec3(1.0, 1.0, 1.0));
	//glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(m_vertexBufferSize));

	//glm::mat4 cubeModel3 = glm::translate(cubeModel2, glm::vec3(1.0, -1.0, 0.0));
	//MVP = Projection * View * cubeModel3;
	//shader.setUniformMatrix4fv("MVP", MVP);
	//shader.setUniform3fv("u_Color", glm::vec3(1.0, 0.0, 0.0));
	//glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(m_vertexBufferSize));

	//glm::mat4 cubeModel4 = glm::translate(cubeModel1, glm::vec3(0.0, 0.0, 3.0));
	//MVP = Projection * View * cubeModel4;
	//shader.setUniformMatrix4fv("MVP", MVP);
	//shader.setUniform3fv("u_Color", glm::vec3(0.0, 0.5, 0.7));
	//glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(m_vertexBufferSize));

	for (int i = 0; i < m_amountObjects; i++)
	{
		glm::mat4 object = particles[i].getObjectModel();
		glm::mat4 MVP = Projection * View * object;
		shader.setUniformMatrix4fv("MVP", MVP);
		shader.setUniform3fv("u_Color", glm::vec3(Particle::GenerateFloatNumber(0.0f, 1.0f), Particle::GenerateFloatNumber(0.0f, 1.0f), Particle::GenerateFloatNumber(0.0f, 1.0f)));
		glDrawElements(GL_TRIANGLES, m_indexBufferData.size(), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(m_vertexBufferSize));
		particles[i].move();
	}
}


