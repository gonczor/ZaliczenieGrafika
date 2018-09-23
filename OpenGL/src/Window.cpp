#include "Window.h"

#include <iostream>
#include <memory>
#include <VertexBuffer.h>
#include <Program.h>
#include <Shape.h>
#include <SolidSphere.h>
#include <IndexBuffer.h>
#include <glm/gtc/matrix_transform.hpp>


Window::Window(unsigned int widht, unsigned int height)
	:m_widht(widht), m_height(height)
{
	conditions = new Conditions();
	keyboard = new Keyboard(conditions);
}

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


	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW Error\n";
		return -1;
	}

	glfwSetKeyCallback(window, this->getKeyboardOnKeyPressed);

	std::cout << glGetString(GL_VERSION) << '\n';

	GLfloat vertices[]{
		+0.0f, +1.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f
	};

	std::shared_ptr<Shape> sphere = std::make_shared<SolidSphere>(50, 1.0f);
	sphere->generate();

	std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(&sphere->m_vertecies[0], sphere->m_vertecies.size() * sizeof(Vertex));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<const void*>(0));



	std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(&sphere->m_indicies[0], sphere->m_indicies.size() * sizeof(GLushort));
	
	std::string vertexPath = "resources/shaders/vertex_shader.glsl";
	std::string fragmentPath = "resources/shaders/fragment_shader.glsl";

	ShaderSourceCode source = ShaderSourceCode::loadShaderCode(vertexPath, fragmentPath);

	Shader shader(source);
	shader.compile();

	Program program(shader);
	program.attachAndLink();
	program.use();

	program.setColorOfShape("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));

	//glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.5f, 0.0f));
	//glm::mat4 rotation = glm::rotate(glm::mat4(), (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	//glm::mat4 projection = glm::perspective(60.0f, (float)m_widht / (float)m_height, 0.1f, 10.0f);


	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;


	//glm::mat4 Model = glm::mat4(1.0f);

	//glm::mat4 View = glm::lookAt(
	//	glm::vec3(2, 1, 1),
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 1, 0)
	//);

	//glm::mat4 Translation = glm::translate(Model, glm::vec3(0.1f, 0.0f, 0.0f));

	//glm::mat4 Projection = glm::perspective(
	//	glm::radians(45.0f),
	//	static_cast<GLfloat>(m_widht) / static_cast<GLfloat>(m_height),
	//	0.1f,
	//	100.0f
	//);
	//glm::mat4 trans(1.0f);
	//trans = glm::rotate(
	//	trans,
	//	static_cast<GLfloat>(glfwGetTime()), 
	//	glm::vec3(0.0, 1.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	////glm::mat4 u_MVP = Projection * Translation * View * Model;

	//program.setTranslation("MVP", trans);
	//
	//float r = 0.5f;
	glPointSize(5.0f);
	glm::mat4 trans(1.0f);
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	glm::vec3 move(0.0f, 0.0f, 0.02f);
	while (!glfwWindowShouldClose(window))
	{
		this->printConditions();
		glClearColor(0.0f, 0.6f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		

		trans = glm::translate(trans, -move);
		trans += glm::rotate(
			trans,
			0.1f,
			glm::vec3(0.0, 1.0, 1.0)
		);
		
		program.setTranslation("MVP", trans);


		glDrawElements(GL_LINES, sphere->m_indicies.size(), GL_UNSIGNED_SHORT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

void * Window::getKeyboardOnKeyPressed()
{
	return this->keyboard->onKeyPressed;
}

void Window::printConditions()
{
	std::cout << "T: " << this->conditions->getTemperature() << "\tP: " << this->conditions->getPressure() << std::endl;
}
