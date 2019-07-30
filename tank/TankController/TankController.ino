
#include <WiFi.h>
#include <MQTT.h>
#include <analogWrite.h>
#include <ArduinoJson.h>

#include "config.h";
#include "IotClient.h";
#include "TB6612Drive.h"


WiFiClient net;
MQTTClient client;

IotClient iotClient;
TB6612Drive _TB6612Drive = TB6612Drive();



void connect()
{
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!iotClient.connect())
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  // client.unsubscribe("/hello");
}

void onAction(String &action, JsonObject &params)
{
  Serial.println("on action:" + action);
  if (action == "stop")
  {
    _TB6612Drive.stop();
  }
  else if (action == "forward")
  {
    _TB6612Drive.forward(20);
  }
  else if (action == "backward")
  {
    _TB6612Drive.backward(20);
  }
  else if (action == "right")
  {
    _TB6612Drive.right(20);
  }
  else if (action == "left")
  {
    _TB6612Drive.left(20);
  }
  else
  {
    Serial.println("error");
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(server, port, net);
  iotClient.begin(&client, mqttUser, mqttPass, deviceUUID);
  iotClient.onAction(onAction);
  _TB6612Drive.setup();

  connect();

}

void loop()
{
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected())
  {
    connect();
  }
}
