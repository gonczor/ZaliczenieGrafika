#include "Keyboard.h"


Keyboard::Keyboard(Conditions * conditions)
{
	this->conditions = conditions;
}

Keyboard::~Keyboard()
{
}

void Keyboard::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;

	switch (key)
	{
	case GLFW_KEY_Q:
		this->increaseTemperature();
		break;
	case GLFW_KEY_A:
		this->decreaseTemperature();
		break;
	case GLFW_KEY_W:
		this->increasePressure();
		break;
	case GLFW_KEY_S:
		this->decreasePressure();
		break;
	}
}

void Keyboard::increaseTemperature()
{
	this->conditions->setTemperature(this->conditions->getTemperature() + 1);
}

void Keyboard::decreaseTemperature()
{
	this->conditions->setTemperature(this->conditions->getTemperature() - 1);
}

void Keyboard::increasePressure()
{
	this->conditions->setPressure(this->conditions->getPressure() + 1);
}

void Keyboard::decreasePressure()
{
	this->conditions->setPressure(this->conditions->getPressure() - 1);
}
