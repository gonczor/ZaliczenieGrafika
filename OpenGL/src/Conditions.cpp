#include "Conditions.h"


Conditions::Conditions()
{
	this->temperature = Conditions::INITIAL_TEMEPRATURE;
	this->pressure = Conditions::INITIAL_PRESSURE;
}


Conditions::~Conditions()
{
}

void Conditions::setTemperature(int temperature)
{
	this->temperature = temperature;
}

void Conditions::setPressure(int pressure)
{
	this->pressure = pressure;
}

int Conditions::getTemperature()
{
	return this->temperature;
}

int Conditions::getPressure()
{
	return this->pressure;
}
