#include "Shader.h"

#include <iterator>
#include <fstream>
#include <string>
#include <iterator>

Shader::Shader(const ShaderSourceCode& source)
	:shaderSourceCode(source)
{}

Shader::~Shader()
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

//std::string Shader::loadShader(std::string filepath) const
//{
//	std::ifstream shaderInput(filepath);
//
//	if (!shaderInput.good())
//	{
//		std::cout << "Unable to load file: " << filepath << '\n';
//	}
//
//	return { std::istreambuf_iterator<char>(shaderInput), std::istreambuf_iterator<char>() };
//}

void Shader::compile()
{
	const char * vertexShaderCode = shaderSourceCode.vertex.c_str();
	const char * fragmentShaderCode = shaderSourceCode.fragment.c_str();

	std::cout << vertexShaderCode << fragmentShaderCode << std::endl;

	m_vertexShaderID = complieEachShader(GL_VERTEX_SHADER, vertexShaderCode);
	m_fragmentShaderID = complieEachShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
}

void Shader::setShaderSourceCode(const ShaderSourceCode & sourceCode)
{
	this->shaderSourceCode = sourceCode;
}

GLuint Shader::getVertexShader() const
{
	return m_vertexShaderID;
}

GLuint Shader::getFragmentShader() const
{
	return m_fragmentShaderID;
}

GLuint Shader::complieEachShader(GLuint type, const char * source)
{
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint complieStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &complieStatus);
	if (complieStatus != GL_TRUE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar * buffer = new char[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);

		std::cout <<(type == GL_VERTEX_SHADER ? "Vertex shader error\n" : "Fragment shader error\n")  << buffer << '\n';

		delete[] buffer;
	}
	
	return shaderID;
}

ShaderSourceCode ShaderSourceCode::loadShaderCode(std::string vertexpath, std::string fragmentpath)
{
	std::ifstream vertexInput(vertexpath), fragmentInput(fragmentpath);

	if (!vertexInput.good() && !fragmentInput.good())
	{
		std::cout << "File not found\n";
	}

	return {
		{std::istreambuf_iterator<char>(vertexInput), std::istreambuf_iterator<char>()},
		{std::istreambuf_iterator<char>(fragmentInput), std::istreambuf_iterator<char>()}
	};
}
