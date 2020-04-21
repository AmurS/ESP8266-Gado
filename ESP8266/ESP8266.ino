#include <ESP8266WiFi.h> 
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

//Wi-fi
WiFiClient WIFI_CLIENT;
const char* ssid = "Wai-Fu"; //Your WiFi Name
const char* password = "Ndakada123";  //Your Wifi Password
WiFiServer server(80);

//Static IP
IPAddress staticIP(192, 168, 137, 100); //ESP static ip
IPAddress gateway(192, 168, 137, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(192, 168, 7, 3);  //DNS

//BMP180
Adafruit_BMP085 bmp; //declare as bmp
#define I2C_SCL 5 //ESP Pin SCL
#define I2C_SDA 4 //ESP Pin SCA

//DHT11
#define DHTPIN 2 //ESP Pin
#define DHTTYPE    DHT11  //DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);
float t = 0.0;
float h = 20.0;

//MQTT
const char* host = "192.168.137.13"; //MQQT Broker IP
int port = 1883; //MQTT Broker port
const char* user = "amur"; //MQTT Broker Username
const char* pass = "inc"; //MQTT Broker Password
const char* clientid = "esp8266a"; //MQTT Client ID
#undef  MQTT_MAX_PACKET_SIZE // un-define MQTT max packet size
#define MQTT_MAX_PACKET_SIZE 500  // fix for MQTT client dropping messages over 128B

PubSubClient mqtt;
void reconnect() {
  mqtt.setServer(host, port);
  mqtt.setClient(WIFI_CLIENT);
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    // Attempt to connect
    Serial.println("Attempt to connect to MQTT broker");
    mqtt.connect(clientid, user, pass);
    // Wait some time to space out connection requests
    delay(3000);
  }
  Serial.println("MQTT connected");
}

void setup() {
  Serial.begin(115200);
  delay(10); 
  Serial.println();
  Serial.println(); 
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.disconnect();
  WiFi.hostname(clientid);  
  WiFi.config(staticIP, gateway, subnet, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
  Serial.println("Telemetry started.");
  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }

}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float AMSL = (bmp.readAltitude() + bmp.readAltitude(102000))/2; //Mean Sea Level abal 
  
  // Check MQTT
  if (!mqtt.connected()) {
    Serial.println("MQTT error");
    reconnect();
  }

  //Json fuckery
  StaticJsonDocument<141> doc; // arduinojson.org/assistant to compute the byte capacity.
  JsonObject test = doc.to<JsonObject>();
  test["Temperature"] = (bmp.readTemperature()+ t) /2; //Temp avr from BMP180 and DHT11
  test["Altitude"] = AMSL;  //Height Above Mean Sea Level
  test["Pressure"] = bmp.readPressure()* 0.00029530; //Pressure Pa to inHG
  test["Pressure at Sea Level"] = bmp.readSealevelPressure()* 0.00029530; //Pressure calculated at sea level Pa to inHG
  test["Humidity"] = h; //Humidity from DHT11
  char buffer[150];
  serializeJson(doc, buffer);

  //push MQTT
  mqtt.publish("test", buffer);

  // delay for sleep
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP); //WIFI_LIGHT_SLEEP mode
  delay(10000); //10sec
  
}
