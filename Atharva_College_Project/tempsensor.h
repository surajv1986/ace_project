#ifndef _TEMPSENSOR_H 
#define _TEMPSENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20PIN 16

/* Create an instance of OneWire */
OneWire oneWire(DS18B20PIN);

DallasTemperature sensor(&oneWire);

inline void dsb_setup(void)
{
  /* Start the DS18B20 Sensor */
  sensor.begin();
}


float read_temperature(void)
{
	float tempinC = 0.00;

	sensor.requestTemperatures(); 
	tempinC = sensor.getTempCByIndex(0);
	
	return tempinC;
}



#endif
