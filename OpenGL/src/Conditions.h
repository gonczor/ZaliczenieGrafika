#pragma once
class Conditions
{
	/*
	Conditions in Si units. Temperature in Kelvins and pressure in Pascals.
	Initial conditions: 273K, 10000 Pa. 
	*/
public:
	Conditions();
	~Conditions();
	static const int INITIAL_TEMEPRATURE = 273;
	static const int INITIAL_PRESSURE = 10000;

	void setTemperature(int);
	void setPressure(int);
	int getTemperature();
	int getPressure();
private:
	int pressure;
	int temperature;
};

