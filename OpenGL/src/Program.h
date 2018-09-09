#pragma once
#include <Shader.h>
#include <glm\glm.hpp>
class Program
{
public:
	Program(Shader &shader);
	~Program();
	void attachAndLink();
	void use();
	
	void setColorOfShape(const char* variableName, glm::vec3 color);

private:
	bool checkProgramStatus();

private:
	GLuint m_programID = 0;
	Shader &m_shader;
};

