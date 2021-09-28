//#include "btecg.h"
#include "ad8232_iot.h"
#include "max30100.h"
#include "tempsensor.h"
#include <WiFi.h>

 
#define WIFISSID "Airtel_9819401408" // Put your Wifi SSID here
#define PASSWORD "air43234" // Put your WIFI password here



void wifi_setup()
{
  
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  
 
  Serial.println();
  Serial.print("Waiting for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
}


void setup() {

   Serial.begin(115200); 
   //wifi_setup();
   ecg_setup();
   max30100_setup();
   dsb_setup();
   
 
}

void loop() {
  
  float temperature = 0.00;
  // put your main code here, to run repeatedly:
   read_ecg_data();
   read_max30100_params();
   temperature = read_temperature();
   Serial.println("temperature in centigrade is :");
   Serial.println(temperature);
   Serial.println("%C");
 //  delay(1000);
}
