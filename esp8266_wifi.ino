#include "ESP8266WiFi.h"


 const char* ssid = "UnifiAP";
 const char* password =  "programmer123";
uint8_t payload[3];
WiFiServer wifiServer(80);


void setup() {
    // put your setup code here, to run once:
    pinMode(D5,OUTPUT);
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


  WiFiClient client = wifiServer.available();
 
  if (client) 
  {
    
 
    while (client.connected()) {
 
      while (client.available()>=2) {


      //  for(int x=0; x<2; x++)
      //    {
      //      payload[x] = client.read(); //2bytes of DATA
      //      if (x==1)
      //      {
      //      Serial.print("Datas is 1: " );
      //      Serial.print(payload[1], HEX);
      //      }
      //      else if(x==0)
      //      {
      //        Serial.print("Datas is 0: ");
      //        Serial.print(payload[0], HEX);
             
      //      }
      //    } 
      client.read(payload,2);
      digitalWrite(D5, HIGH);
      Serial.write(payload[0]);
      Serial.write(payload[1]);

      }
 
      delay(10);
      digitalWrite(D5, LOW);
    }
 
    client.stop();
    //Serial.println("Client disconnected");

  }
  else
  {
    digitalWrite(D5, LOW);
  }
}
