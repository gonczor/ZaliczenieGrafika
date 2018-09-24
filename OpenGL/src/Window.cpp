#include "Window.h"

#include <iostream>
#include <memory>
#include <Program.h>
#include <Shape.h>
#include <SphereMesh.h>
#include <Texture.h>
#include <Render.h>
#include <glm/gtc/matrix_transform.hpp>


Window::Window(unsigned int widht, unsigned int height)
	:m_widht(widht), m_height(height)
{}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Window::initWindow()
{
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(m_widht, m_height, "Perfect Gas", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK) 
	{
		std::cerr << "GLEW Error\n";
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	std::cout << glGetString(GL_VERSION) << '\n';

	SphereMesh sphere(10, 10, 0.2f);
	sphere.generate();

	Render render(1000, sphere);
	render.pushDataToBuffer();

	std::shared_ptr<Texture> tex = std::make_shared<Texture>("resources/textures/bricks.jpg");
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), static_cast<const void*>(0));
	tex->bind();

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, m_widht, m_height);

		render.paintSpheres();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

bool Window::initGLFW()
{
	return false;
}

bool Window::initOpengl()
{
	return false;
}

void Window::pushDataToBuffer()
{
}
