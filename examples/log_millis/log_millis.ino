/**
 * log.ino
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

// This are the graylog dependencies
#include <UDPTransport.h>
#include <Message.h>
#include <Publisher.h>

// WiFi settings
const char ssid[] = "MY-SSID";
const char password[] = "MY-PASSWORD";

// Here we create the transport and the publisher objects
// The transport can be either UDP, TCP, HTTP, etc (right now UDP only is implemented)
// It takes an IP address or a host name

// UDPTransport transport = UDPTransport("log.mysite.net", 12201);
UDPTransport transport = UDPTransport(IPAddress(192, 168, 1, 27), 12201);
Publisher publisher = Publisher(&transport);

// We will use this just to avoid creating many messages in our functions
Message message = Message("");

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected!");
}

void loop() {
  message = Message("this is a test");
  publisher.publish(&message);

  message = Message("Current millis");
  message.set("millis", millis());
  publisher.publish(&message);

  Serial.println("Data sent :)");
  delay(100);
}
