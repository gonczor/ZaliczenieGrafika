#pragma once
#include <Shader.h>
#include <glm\glm.hpp>
class ShaderProgram
{
public:
	ShaderProgram(std::string vertexpath, std::string fragmentpath);
	~ShaderProgram();
	void attachAndLink(const Shader& shader);
	void use();

	void setUniform1i(const char * variableName, GLint value);
	void setUniform3fv(const char* variableName, glm::vec3 color);
	void setUniformMatrix4fv(const char * variableName, glm::mat4 translation);

	GLuint getProgramID();


private:
	bool checkProgramStatus();

private:
	GLuint m_programID = 0;
};

