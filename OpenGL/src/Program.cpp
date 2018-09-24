#include "Program.h"
#include <glm/gtc/type_ptr.hpp>



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

void ShaderProgram::setUniform1i(const char * variableName, GLint value)
{
	GLint location = glGetUniformLocation(m_programID, variableName);
	if (location == -1)
	{
		return;
	}
	glUniform1i(location, value);
}

void ShaderProgram::setUniform3fv(const char * variableName, glm::vec3 color)
{

	GLint location = glGetUniformLocation(m_programID, variableName);
	if (location == -1)
	{
		return;
	}
	glUniform3fv(location, 1, &color[0]);
}

void ShaderProgram::setUniformMatrix4fv(const char * variableName, glm::mat4 translation)
{

	GLint location = glGetUniformLocation(m_programID, variableName);
	if (location == -1)
	{
		return;
	}
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


GLuint ShaderProgram::getProgramID()
{
	return m_programID;
}