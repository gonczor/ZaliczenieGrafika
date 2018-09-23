#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Conditions.h"
/*
	Used to handle conditions. Collects keyboard input and manipulates conditions.
	Keys are responsible for following actions:
		- Q - increase temperature by 1K,
		- A - decrease temperature by 1K,
		- W - increase pressure by 1Pa,
		- S - decrease pressure by 1Pa.
*/
class Keyboard
{
public:
	Keyboard(Conditions*);
	~Keyboard();
	void onKeyPressed(unsigned char key);
private:
	Conditions* conditions;
	void increaseTemperature();
	void decreaseTemperature();
	void increasePressure();
	void decreasePressure();
};

