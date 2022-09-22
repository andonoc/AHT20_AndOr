#include "AHT20_AndOr.h"

AHT20 AHT;

float temperature;
float humidity;
uint8_t humidityINT;


void setup() {
  Serial.begin(250000);
  AHT.begin();

}

void loop() {
  AHT.getTemperature(&temperature);
  Serial.print("temperature: ");
  Serial.println(temperature);
  AHT.getHumidity(&humidity);
  humidityINT = (uint8_t)humidity;
  Serial.print("humidity: ");
  Serial.println(humidityINT);
  delay(2000);

}
