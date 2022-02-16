#include <MQTTClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>
#include <stdio.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <MQTTJsonParse.h>
WiFiClient espClient;
PubSubClient client(espClient);
extern MQTT_CONNECTION_ID_INFO ESPTopic[MAX_MESSAGE_PUB_SUB];

const char *ssid = "testcase_2";      // Enter your WiFi name
const char *password = "12345612zxc"; // Enter WiFi password
const char *mqtt_broker = "driver.cloudmqtt.com";
const char *topic = "esp32/test";
const char *mqtt_username = "burlgbdf";
const char *mqtt_password = "_FEoLObHd01P";
const int mqtt_port = 18675;

void message_pub(MQTT_CONNECTION_ID topic_id, const char *payload)
{
    if (client.publish(ESPTopic[topic_id].topic_name, payload) == 1)
    {
        Serial.print("response success topic: ");
        Serial.printf(ESPTopic[topic_id].topic_name);
        Serial.println();
    }
    else
    {
        Serial.println("response failed");
    }
}
void init_topic(void)
{
    uint8_t i = 0;
    for (i = 0; i < MAX_MESSAGE_PUB_SUB; i++)
    {
        ESPTopic[i].topic_id = i;
    }
    sprintf(ESPTopic[REALTIME_TOPIC_ID].topic_name, "esp32/realtime");
    sprintf(ESPTopic[SETTING_TOPIC_ID].topic_name, "esp32/setting");
    sprintf(ESPTopic[SETTING_RESPONE_TOPIC_ID].topic_name, "esp32/setting_respone");
    sprintf(ESPTopic[PARAMS_TOPIC_ID].topic_name, "esp32/params");
    sprintf(ESPTopic[PARAMS_RESPONE_TOPIC_ID].topic_name, "esp32/params_respone");
    sprintf(ESPTopic[ESP_INFO_TOPIC_ID].topic_name, "esp32/info");
    sprintf(ESPTopic[ESP_INFO_RESPONE_TOPIC_ID].topic_name, "esp32/info_respone");
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    MQTTJSONParser_parse(topic, (char *)payload);
}
void mqtt_init(void)
{
    init_topic();
    Serial.begin(9600);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected())
    {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Public emqx mqtt broker connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    int i;
    for (i = 1; i < MAX_MESSAGE_PUB_SUB; i += 2)
    {

        if (client.subscribe(ESPTopic[i].topic_name) == 1)
        {
            Serial.printf("Subscribe to topic %s\n", ESPTopic[i].topic_name);
        }
        else
        {
            Serial.printf("Failed to subscribe to topic %s\n", ESPTopic[i].topic_name);
        }
    }
}

void real_time_update(void)
{
    message_pub(REALTIME_TOPIC_ID, (char *)random(0, 100));
}
void client_loop(void)
{
    client.loop();
}
