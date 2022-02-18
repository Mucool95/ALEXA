#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const char ssid[] = "Redmi";  // your network SSID (name)
const char pass[] = "cvwv6562";   // your network password
WiFiClient  client;
unsigned long counterChannelNumber = 983229;            // Channel ID
const char * myCounterReadAPIKey = "PMDYKEPJKF0XS1T1"; // Read API Key
const int FieldNumber1 = 1;  // The field you wish to read
const int FieldNumber2 = 2;  // The field you wish to read
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  pinMode(D0, OUTPUT);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  ThingSpeak.begin(client);
}

void loop()
{
  String val = ThingSpeak.readStringField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  if (val == "on")
  {
    digitalWrite(D0, HIGH);
    Serial.println("LED ON");
  }
  if (val == "off")
  { digitalWrite(D0, LOW);
      Serial.println("LED OFF");
  }

  int statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    Serial.print("Command: ");
    Serial.println(val);
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
}
