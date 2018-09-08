#pragma once
#include <Shader.h>

class Program
{
public:
	Program(Shader &shader);
	~Program();
	void attachAndLink();
	void use();


private:
	bool checkProgramStatus();

private:
	GLuint m_programID = 0;
	Shader &m_shader;
};

