#ifndef _AD8232_IoT_H    // Put these two lines at the top of your header file.
#define _AD8232_IoT_H    // (Use a suitable name, usually based on the file name.)
#include <PubSubClient.h>

#define TOKEN "your token" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "1234a5d6798" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices
 
/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL "Sensor" // Assign the variable label
#define DEVICE_LABEL "Demo" // Assig the device label
 
#define SENSOR A0 // Set the A0 as SENSOR
#define L0_MINUS 40
#define L0_PLUS 41
#define LOW 0
#define HIGH 1

void ecg_setup()
{
  pinMode(SENSOR, INPUT);
  pinMode(L0_PLUS, INPUT); // Setup for leads off detection LO +
  pinMode(L0_MINUS, INPUT); // Setup for leads off detection LO -  
}

void read_ecg_data()
{
  if((digitalRead(L0_PLUS) == HIGH)||(digitalRead(L0_MINUS) == HIGH)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      Serial.println(analogRead(SENSOR));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);

}

#endif _AD8232_IoT_H 
