#include "Keyboard.h"


Keyboard::Keyboard(Conditions * conditions)
{
	this->conditions = conditions;
}

Keyboard::~Keyboard()
{
}

void Keyboard::onKeyPressed(unsigned char key)
{
	switch (key)
	{
	case 'Q':
		this->increaseTemperature();
		break;
	case 'A':
		this->decreaseTemperature();
		break;
	case 'W':
		this->increasePressure();
		break;
	case 'S':
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
