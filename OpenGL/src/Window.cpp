#include "Window.h"

#include <iostream>
#include <memory>
#include <VertexBuffer.h>
#include <Program.h>
#include <Shape.h>
#include <SolidSphere.h>
#include <IndexBuffer.h>


Window::Window(unsigned int widht, unsigned int height)
	:m_widht(widht), m_height(height)
{}

Window::~Window()
{
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


	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW Error\n";
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << '\n';

	GLfloat vertices[]{
		+0.0f, +0.5f,
		-0.5f, -0.5f,
		+0.5f, -0.5f
	};

	std::shared_ptr<Shape> sphere = std::make_shared<SolidSphere>(5, 1);
	sphere->generate();

	std::shared_ptr<VertexBuffer> object = std::make_shared<VertexBuffer>(vertices, 6*sizeof(GLfloat));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, 0);
	//
	std::string vertexPath = "resources/shaders/vertex_shader.glsl";
	std::string fragmentPath = "resources/shaders/fragment_shader.glsl";

	ShaderSourceCode source = ShaderSourceCode::loadShaderCode(vertexPath, fragmentPath);

	Shader shader(source);
	shader.compile();

	Program program(shader);
	program.attachAndLink();
	program.use();
	program.setColorOfShape("u_Color", glm::vec3(0.2f, 0.7f, 1.0f));

	

	float r = 0.5f;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	return 0;
}
