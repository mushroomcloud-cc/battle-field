#include <MQTT.h>

#include "IotClient.h"

class MQTTClient;

IotClient *instance = nullptr;

void IotClient::begin(MQTTClient *mqttClient, String user, String password, String clientUUID)
{
    this->mqttClient = mqttClient;
    this->clientUUID = clientUUID;
    this->user = user;
    this->password = password;

    this->mqttClient->onMessage(this->messageReceived);
    instance = this;
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

void  IotClient::messageReceived(String &topic, String &payload)
{
    Serial.println("incoming: " + topic + " - " + payload);
    // TODO check topic


   
    if(instance != nullptr && instance->actionCallback != nullptr) {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        String actionName = obj["name"];
        auto paramMap = obj["paramMap"].as<JsonObject>();
        instance->actionCallback(actionName,paramMap);
    }
    
}

void IotClient::onAction(ActionCallback callback) {
    this->actionCallback = callback;
}