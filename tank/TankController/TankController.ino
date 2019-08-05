#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>
#include <analogWrite.h>
#include <ArduinoJson.h>
#include <MPU6050_tockn.h>

#include "config.h";
#include "IotClient.h";
#include "TB6612Drive.h"



TB6612Drive _TB6612Drive = TB6612Drive();

WiFiClient net;
MQTTClient client;

IotClient iotClient;
MPU6050 mpu6050(Wire);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(server, port, net);
  iotClient.begin(&client, mqttUser, mqttPass, deviceUUID);
  iotClient.onAction(onAction);
  _TB6612Drive.setup();

  Wire.begin();
  // Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);


  connect();
}

unsigned long lastMillis = 0;
void loop()
{
  client.loop();
  // delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected())
  {
    connect();
  }

  mpu6050.update();
 if (millis() - lastMillis > 400)
    {
      lastMillis = millis();
      Serial.print("ypr\t");
      Serial.println(mpu6050.getAngleZ());
      DynamicJsonDocument data(1024);
      data["yaw"] = mpu6050.getAngleZ();

      String json = "";
      serializeJson(data, json);
      Serial.println("send json:" + json);
      iotClient.publishJsonData(json);
    }


}

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