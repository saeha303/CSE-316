
#include "CTBot.h"
#include "WiFi.h"
CTBot myBot;

String ssid = "your wifi/hotspot name";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "your wifi/hotspot password"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "your telegram bot token";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
					
int water_level;
uint8_t inpin=34;
int flag=0;
void setup() {
	// initialize the Serial
	Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  pinMode (inpin,INPUT);
  Serial.println("asdfghjk.");
	

	// connect the ESP8266 to the desired access point
	myBot.wifiConnect(ssid, pass);
  Serial.println("hos na kn.");
	// set the telegram bot token
	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else{
    Serial.println("\ntestConnection NOK");
  }
		
}

void loop() {
	// a variable to store telegram message data
	TBMessage msg;

	water_level=digitalRead(inpin);
  Serial.println(water_level);
  int64_t id1=(int64_t)5356804592;
  if(water_level==0)
		{	 
    Serial.println("Water level is low");
    flag=1;
    myBot.sendMessage(id1, "Water level is low, pleaseeeeee fill me up"); 
    delay(7000);
    } 
  else{
    Serial.println("Water level is high");
     if(flag==1)
      { myBot.sendMessage(id1, "Water level is high now"); 
      flag=0;
      }
  }
	delay(500);
}
