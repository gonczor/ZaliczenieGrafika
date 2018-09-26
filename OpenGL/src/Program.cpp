#include "Program.h"
#include <glm/gtc/type_ptr.hpp>
#include <iterator>


ShaderProgram::ShaderProgram(std::string vertexpath, std::string fragmentpath)
	:m_programID(glCreateProgram())
{
	ShaderSourceCode source = ShaderSourceCode::loadShaderCode(vertexpath, fragmentpath);
	Shader shader(source);
	shader.compile();
	attachAndLink(shader);
	use();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programID);
}

void ShaderProgram::attachAndLink(const Shader &shader)
{
	glAttachShader(m_programID, shader.getVertexShader());
	glAttachShader(m_programID, shader.getFragmentShader());
	glLinkProgram(m_programID);
}

void ShaderProgram::use()
{
	if (checkProgramStatus()) 
	{
		glUseProgram(m_programID);
	}
}

void ShaderProgram::setUniform(const char * variableName, const GLint& value)
{
	GLint location = getUniformLocation(variableName);
	glUniform1i(location, value);
}

void ShaderProgram::setUniform(const char * variableName, const glm::vec3& color)
{
	GLint location = getUniformLocation(variableName);
	glUniform3fv(location, 1, glm::value_ptr(color));
}

void ShaderProgram::setUniform(const char * variableName, const glm::mat4& translation)
{

	GLint location = getUniformLocation(variableName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(translation));
}

bool ShaderProgram::checkProgramStatus()
{
	GLint linkStatus;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar * buffer = new char[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(m_programID, infoLogLength, &bufferSize, buffer);

		std::cout << "Link error\n";
		std::cout << buffer << '\n';

		delete[] buffer;
		return false;
	}

	return true;
}


GLint ShaderProgram::getUniformLocation(const char * variableName)
{
	std::map<std::string, GLint>::const_iterator it = m_uniformsLocations.find(variableName);
	if (it != m_uniformsLocations.cend())
	{
		return it->second;
	}
	else
	{
		GLint location = glGetUniformLocation(m_programID, variableName);
		m_uniformsLocations.insert(std::pair<std::string, GLint>(variableName, location));
		return location;
	}
}

GLuint ShaderProgram::getProgramID()
{
	return m_programID;
}