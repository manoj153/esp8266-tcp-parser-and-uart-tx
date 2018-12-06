#include "ESP8266WiFi.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5 

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
 
 String temp;
 const char* ssid = "UnifiAP";
 const char* password =  "programmer123";
uint8_t payload[3];
WiFiServer wifiServer(80);


void setup() {
    // put your setup code here, to run once:
    sensors.begin();
    pinMode(D5,OUTPUT);
    digitalWrite(D5, LOW);
    Serial.begin(9600);
    delay(500);

    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}


void loop() 
{

sensors.requestTemperatures();

temp = sensors.getTempCByIndex(0);
  WiFiClient client = wifiServer.available();
 
  if (client) 
  {
    
    
 
    while (client.connected()) {

      digitalWrite(D5, HIGH);

      if (client.available()==1)
      {
        client.print(temp);
        //Serial.println("dd");
        client.stop();
      }

      else
      {
      while (client.available()>=2) {


      client.read(payload,2);
      client.stop();
      //digitalWrite(D5, LOW);
      Serial.write(payload[0]);
      Serial.write(payload[1]);

      }
      
      }
 
      delay(10);
      
    }
 
    //client.stop();
    //Serial.println("Client disconnected");

  }

  digitalWrite(D5, LOW);
  
}
