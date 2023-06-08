#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <string.h>
#include <ThingSpeak.h>
#include "secrets.h"
WiFiClient client;

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
       Serial.print(".");
  }
  Serial.println();
  Serial.print("connected!");
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
  long temp_out = ThingSpeak.readLongField(counterChannelNumber, 2, SECRET_READ_API);
  long temp_in = ThingSpeak.readLongField(counterChannelNumber, 1, SECRET_READ_API);
  delay(20);
  if (ThingSpeak.getLastReadStatus()==200)
  {
    if (temp_out > temp_in) digitalWrite(LED_BUILTIN,LOW); //reversed logic 
    else                    digitalWrite(LED_BUILTIN,HIGH);
    WiFi.mode(WIFI_SHUTDOWN);
    Serial.print("out: ");
    Serial.print(temp_out);
    Serial.print("   in: ");
    Serial.println(temp_in);
    delay (120000);
  }
  else
  {
      Serial.println("sth went wrong ");
    for(int i = 0 ; i<100; i++){
    digitalWrite(LED_BUILTIN,LOW);
    delay (1000);
    digitalWrite(LED_BUILTIN,HIGH);
    delay (100);
    }
  }
}