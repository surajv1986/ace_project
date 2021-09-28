

#ifndef _BTECG_H    // Put these two lines at the top of your file.
#define _BTECG_H    // (Use a suitable name, usually based on the file name.)

#include "BluetoothSerial.h"
#define BT_INIT_SUCCESS 0
#define BT_INIT_FAILURE -1

#define LED_BUILTIN 2 //pin with LED to turn on when BT connected

BluetoothSerial ESP_BT; // Object for Bluetooth
// global vars
boolean BT_cnx = false;

/*
 *@brief : A callback function to be triggered whenever a client device connects to ESP32 MCU over bluetooth.
 *@param: An instance of esp_spp_cb_event.
 *@param: An instance of esp_spp_cb_param_t. 
 *@return: None. 
 */
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
    digitalWrite(LED_BUILTIN, HIGH);
    BT_cnx = true;
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    Serial.println("Client disconnected");
    digitalWrite(LED_BUILTIN, LOW);
    BT_cnx = false;
    //ESP.restart();
  }

  	
}
/*
 *@brief : A function to initialise the bluetooth module for ESP32 MCU.
 *@param: None.
 *@return: 0 on Success, -1 on Failure  
 */
int initialise_bluetooth(void)
{
	// initialize digital pin 2 as an output.
  	pinMode(LED_BUILTIN, OUTPUT);
  	// initialize the serial communication:
  	Serial.begin(9600);
  	Serial.println(); // blank line in serial ...
  	pinMode(41, INPUT); // Setup for leads off detection LO +
  	pinMode(40, INPUT); // Setup for leads off detection LO -
  	// initialize the serial BT communication:
  	ESP_BT.register_callback(callback);
  	if(!ESP_BT.begin("ESP32_ECG")){
   		 return BT_INIT_FAILURE;
  	}else{
    		 return BT_INIT_SUCCESS;
  	}

} 
	
/*
 *@brief : A function to print measured ECG Graph on connected bluetooth client device.
 *@param: A void pointer to parameter list as specified by RTOS standards.
 *@return: None.  
 */
void make_ECG_graph(void *parameter)
{
	while (1) {
			if((digitalRead(40) == 1)||(digitalRead(41) == 1)){
            		Serial.println('!');
            		ESP_BT.println('!');
        		} else {
                		// send the value of analog input 0 to serial:
                		Serial.println(analogRead(A0));
                		//Do the same for blutooth
                		if(BT_cnx){
                               			ESP_BT.print('E'); 
                               			ESP_BT.println(analogRead(A0));
                	} 
        	}
      		 //Wait a little to keep serial data from saturating
      		delay(1000);
     }
}

#endif _BTECG_H    // Put this line at the end of your file.
