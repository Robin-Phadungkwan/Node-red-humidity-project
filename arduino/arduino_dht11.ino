// GEMAAKT DOOR ROBIN PHADUNGKWAN

#include <DHT.h>
#include <DHT_U.h>

#include <dht11.h>
#define DHT11PIN A5

dht11 DHT11;

void setup() // opzet, een keer uitgevoerd
{
  pinMode(9,OUTPUT); //red
  pinMode(10,OUTPUT); //green
  Serial.begin(9600); // serial monitor
}

void loop() // wordt uitgevoerd tot stroomverlies of overschrijding
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);
  if (DHT11.humidity <= 40){
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
  }
  else if(DHT11.humidity >= 60){
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
  }
  else{
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
  }
  
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  delay(2000);
}