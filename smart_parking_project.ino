#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUJNTU1S12";
const char* password = "YOUJNTU1S12";

#define trig D5
#define echo D6

#define ORG "s0tqk2"
#define DEVICE_TYPE "nodemcu"
#define DEVICE_ID "12345"
#define TOKEN "sf(a6OoPnZ4&u23b1d"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishtopic[] = "iot-2/evt/ultrasonic/fmt/json";

char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
WiFiClient wifiClient;
PubSubClient client(server, 1883,wifiClient);
void setup() {
  
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(115200);

  Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
 { 
  delay(500);
  Serial.print(".");
 } 
 Serial.println("");
 
 Serial.print("WiFi connected, IP address: ");
 Serial.println(WiFi.localIP());
}

void loop() {
  
  int duration;
  float distance;
  digitalWrite(trig,LOW);
  delay(1000);
  digitalWrite(trig,HIGH);
  delay(1000);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration*0.034)/200;
  Serial.print("obstacle is at a distance: ");
  Serial.println(distance);
  PublishData(distance);
delay(1000);
}

void PublishData(float distance)
{
 if (!!!client.connected()) 
 {
  Serial.print("Reconnecting client to ");
  Serial.println(server);
  while (!!!client.connect(clientId, authMethod, token))
  {
   Serial.print(".");
   delay(500);
  }
  Serial.println();
 }
  String payload = "{\"d\":{\"distance\":";
  payload += distance;
  payload += "}}";
 Serial.print("Sending payload: ");
 Serial.println(payload);
  
 if (client.publish(publishtopic, (char*) payload.c_str())) 
 {
 Serial.println("Publish ok");
 } 
 else 
 {
 Serial.println("Publish failed");
 }
}
