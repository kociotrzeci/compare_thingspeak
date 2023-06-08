#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>
#include <ThingSpeak.h>
#include "secrets.h"
const char * myCounterReadAPIKey = "J90M1D8KVRXJNNFF";
WiFiClient client;

void setup_wifi()
{
  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    //   Serial.print(".");
  }
//  Serial.println();
//  Serial.print("connected!");
}
void setup()
{
  WiFi.mode(WIFI_STA);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(115200);
  ThingSpeak.begin(client);
}
void loop()
{
  WiFi.mode(WIFI_STA);
  setup_wifi();
  long temp_out = ThingSpeak.readLongField(counterChannelNumber, 1, myCounterReadAPIKey);
  long temp_in = ThingSpeak.readLongField(counterChannelNumber, 2, myCounterReadAPIKey);
  delay(20);
  if (ThingSpeak.getLastReadStatus()==200)
  {
    if (temp_out < temp_in) digitalWrite(LED_BUILTIN,HIGH);
    else                        digitalWrite(LED_BUILTIN,LOW);
    WiFi.mode(WIFI_SHUTDOWN);
    delay (120000);
  }
  else
  {
    for(int i = 0 ; i<100; i++)
    digitalWrite(LED_BUILTIN,LOW);
    delay (1000);
    digitalWrite(LED_BUILTIN,HIGH);
    delay (100);
  }
}