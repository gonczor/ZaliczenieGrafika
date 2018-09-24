#pragma once
#include<GL\glew.h>

#include <iostream>

struct ShaderSourceCode
{
	std::string vertex;
	std::string fragment;
	static ShaderSourceCode loadShaderCode(std::string vertexpath, std::string fragmentpath);
};

class Shader
{
public:
	friend class ShaderProgram;
	Shader(const ShaderSourceCode &sourceCode);
	Shader(const Shader& other) = delete;
	Shader(Shader&& other) = delete;
	~Shader();

	void compile();
	void setShaderSourceCode(const ShaderSourceCode &sourceCode);
	
	GLuint getVertexShader() const;
	GLuint getFragmentShader() const;

private:
	//std::string loadShader(std::string filepath) const;
	GLuint complieEachShader(GLuint type, const char* source);
	



private:
	ShaderSourceCode shaderSourceCode;
	GLuint m_vertexShaderID = 0;
	GLuint m_fragmentShaderID = 0;
};

