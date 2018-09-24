#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window
{
public:
	Window(unsigned int widht, unsigned int height);
	Window(const Window& other) = delete;
	Window(Window&& other) = delete;
	~Window();

	int initWindow();

private:
	bool initGLFW();
	bool initOpengl();
	void pushDataToBuffer();

private:
	unsigned int m_widht = 0;
	unsigned int m_height = 0;
	GLFWwindow* window = nullptr;

};

