
#include <WiFi.h>
#include <MQTT.h>


#include "IotClient.h";
#include "config.h";


WiFiClient net;
MQTTClient client;


IotClient iotClient;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!iotClient.connect()) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");


  // client.unsubscribe("/hello");
}

void onAction(String &action, String &payload) {
  Serial.println("on action:" + action);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(server,port, net);
  iotClient.begin(&client,mqttUser,mqttPass,deviceUUID);
  iotClient.onAction(onAction);
  connect();


}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    //client.publish("/hello", "world");
  }
}
