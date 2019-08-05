#ifndef IOT_CLIENT_H
#define IOT_CLIENT_H

#include <iostream>
#include <MQTT.h>
#include <ArduinoJson.h>

typedef void (*ActionCallback)(String &action,JsonObject &params);


class MQTTClient;
class IotClient
{
private:
    MQTTClient *mqttClient;
    String clientUUID;

    String user;
    String password;

    ActionCallback actionCallback;

public:
    void begin(MQTTClient *mqttClient, String user, String password, String clientUUID);
    static void  messageReceived(String &topic, String &payload);
    void onAction(ActionCallback callback);
    bool connect();
    void publishData(JsonObject data);
    void publishJsonData(String data);
};

#endif
