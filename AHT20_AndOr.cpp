#include "AHT20_AndOr.h"


void AHT20::begin()
{
	Wire.begin();

	Wire.beginTransmission(0x38); // transmit to device #8
	Wire.write(0xBE);
	Wire.endTransmission();    // stop transmitting
}

bool AHT20::startSensor()
{
	//2. Send the 0xAC command directly (trigger measurement).
	//The parameter of this command has two bytes, the first byte
	//is 0x33 and the second byte is 0x00.
	Wire.beginTransmission(0x38); // transmit to device #8
	Wire.write(0xac);
	Wire.write(0x33);
	Wire.write(0x00);
	Wire.endTransmission();    // stop transmitting
	
	//3. Wait for 80ms to wait for the measurement to be completed.
	//If the read status word Bit [7] is 0, it indicates that the
	//measurement is completed, and then six bytes can be read
	//in a row; otherwise, continue to wait.
	unsigned long timer_s = millis();
	while(1)
	{
		if(millis()-timer_s > 200) return 0;        // time out
		Wire.requestFrom(0x38, 1);

		while(Wire.available())
		{
			unsigned char c = Wire.read();
			if(c&0x80 != 0)return 1;      // busy

		}

		delay(20);
	}
}

bool AHT20::getSensor(float *h, float *t)
{
	startSensor();
	Wire.requestFrom(0x38, 6);


	uint8_t str[6];
	uint8_t index = 0;
	while (Wire.available())
	{
		str[index++] = Wire.read(); // receive a byte as character
	}

	if(str[0] & 0x80)return 0;

	uint32_t __humi = 0;
	uint32_t __temp = 0;

	__humi = str[1];
	__humi <<= 8;
	__humi += str[2];
	__humi <<= 4;
	__humi += str[3] >> 4;

	*h = ((float)__humi/1048576.0)*100;

	__temp = str[3]&0x0f;
	__temp <<=8;
	__temp += str[4];
	__temp <<=8;
	__temp += str[5];

	*t = (float)__temp/1048576.0*200.0-50.0;

	return 1;

}

bool AHT20::getTemperature(float *t)
{
	float __t;
	float __h;
	
	int ret = getSensor(&__h, &__t);
	if(0 == ret)return 0;
	
	*t = __t;
	return 1;
}

bool AHT20::getHumidity(float *h)
{
	float __t;
	float __h;
	
	int ret = getSensor(&__h, &__t);
	if(0 == ret)return 0;
	
	*h = __h;
	return 1;
}