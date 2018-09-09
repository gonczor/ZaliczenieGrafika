#include "Program.h"



Program::Program(Shader &shader)
	:m_programID(glCreateProgram()), m_shader(shader)
{}


Program::~Program()
{
	glDeleteProgram(m_programID);
}

void Program::attachAndLink()
{
	glAttachShader(m_programID, m_shader.getVertexShader());
	glAttachShader(m_programID, m_shader.getFragmentShader());
	glLinkProgram(m_programID);
}


void Program::use()
{
	if (checkProgramStatus()) 
	{
		glUseProgram(m_programID);
	}
}

void Program::setColorOfShape(const char * variableName, glm::vec3 color)
{

	GLint location = glGetUniformLocation(m_programID, variableName);
	if (location == -1)
	{
		return;
	}
	glUniform3fv(location, 1, &color[0]);
}

bool Program::checkProgramStatus()
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

		std::cout << buffer << '\n';

		delete[] buffer;
		return false;
	}

	return true;
}
