#pragma once
#include <Shader.h>
#include <glm\glm.hpp>

#include <map>

class ShaderProgram
{
public:
	ShaderProgram(std::string vertexpath, std::string fragmentpath);
	~ShaderProgram();
	void attachAndLink(const Shader& shader);
	void use();

	void setUniform(const char * variableName, const GLint& value);
	void setUniform(const char* variableName, const glm::vec3& color);
	void setUniform(const char * variableName, const glm::mat4& translation);

	GLuint getProgramID();

private:
	bool checkProgramStatus();
	GLint getUniformLocation(const char* variableName);

private:
	GLuint m_programID = 0;
	std::map<std::string, int> m_uniformsLocations;
};

