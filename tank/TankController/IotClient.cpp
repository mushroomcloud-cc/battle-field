#include <MQTT.h>

#include "IotClient.h"

class MQTTClient;

IotClient *iotInstance = nullptr;

void IotClient::begin(MQTTClient *mqttClient, String user, String password, String clientUUID)
{
    this->mqttClient = mqttClient;
    this->clientUUID = clientUUID;
    this->user = user;
    this->password = password;

    this->mqttClient->onMessage(this->messageReceived);
    iotInstance = this;
}

bool IotClient::connect()
{
    bool ret = this->mqttClient->connect(this->clientUUID.c_str(), this->user.c_str(), this->password.c_str());
    if (ret)
    {
        this->mqttClient->subscribe("iot/action/" + this->clientUUID);
    }

    return true;
}

void IotClient::messageReceived(String &topic, String &payload)
{
    Serial.println("incoming: " + topic + " - " + payload);
    // TODO check topic

    if (iotInstance != nullptr && iotInstance->actionCallback != nullptr)
    {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        String actionName = obj["name"];
        auto paramMap = obj["paramMap"].as<JsonObject>();
        iotInstance->actionCallback(actionName, paramMap);
    }
}

void IotClient::publishData(JsonObject data)
{

    String output;
    serializeJson(data, output);
    this->mqttClient->publish("iot/data/" + this->clientUUID, output);
}

void IotClient::publishJsonData(String json) {
     this->mqttClient->publish("iot/data/" + this->clientUUID, json);
}



void IotClient::onAction(ActionCallback callback)
{
    this->actionCallback = callback;
}