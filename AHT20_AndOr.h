// AHT20.h

#ifndef _AHT20_AndOr_h
#define _AHT20_AndOr_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino.h>
#include <Wire.h>

class AHT20{
	
	private:

	bool startSensor();
	public:

	void begin();
	bool getSensor(float *h, float *t);
	bool getTemperature(float *t);
	bool getHumidity(float *h);
};


#endif

