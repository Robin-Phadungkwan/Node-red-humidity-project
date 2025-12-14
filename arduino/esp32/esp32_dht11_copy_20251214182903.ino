// Gemaakt door Robin Phadungkwan

#include <DHT.h> 
#include <DHT_U.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <PubSubClient.h>



const char *ssid = "mijn huisnetwerknaam(express weggehaald)";
const char *password = "Wachtwoord(weggehaald)"; 
const char* mqtt_server = "192.168.178.114";
const char* mqtt_topic = "roomTemp";
const char* clientID = "sensor14";


#define DHTPIN 33
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup(){
  Serial.begin(9600); 
 
  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("wifi verbonden");
  dht.begin();

  client.setServer(mqtt_server,1883);
  client.connect(clientID);
  
  
}
void loop(){
  if (!client.connected()){
    client.connect(clientID);
    Serial.println("to MQTT Broker verbonden");
  }
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT read failed");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %  Temperature: ");
    Serial.print(t);
    Serial.println(" C");

    // publish humidity
    String payload = String(h, 1);
    client.publish(mqtt_topic, payload.c_str());
  }

  delay(2500);  // REQUIRED for DHT11
}
