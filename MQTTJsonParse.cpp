#include <ArduinoJson.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <settings.h>
#include <MQTTClient.h>
MQTT_CONNECTION_ID_INFO ESPTopic[MAX_MESSAGE_PUB_SUB];
// char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
static int setting_json_parse(char *payload);
static int params_json_parse(char *payload);
static int esp_info_json_parse(char *payload);
int MQTTJSONParser_parse(char *topic, char *payload)
{
   if (payload == NULL)
   {
      return -1;
   }
   if (strncmp(topic, ESPTopic[SETTING_TOPIC_ID].topic_name, strlen(ESPTopic[SETTING_TOPIC_ID].topic_name)) == 0)
   {
      setting_json_parse(payload);
   }
   else if (strncmp(topic, ESPTopic[PARAMS_TOPIC_ID].topic_name, strlen(ESPTopic[PARAMS_TOPIC_ID].topic_name)) == 0)
   {
      params_json_parse(payload);
   }
   else if (strncmp(topic, ESPTopic[ESP_INFO_TOPIC_ID].topic_name, strlen(ESPTopic[ESP_INFO_TOPIC_ID].topic_name)) == 0)
   {
      esp_info_json_parse(payload);
   }
   else
   {
      Serial.println("Unknown topic");
   }
   return 0;
}

static int setting_json_parse(char *payload)
{

   StaticJsonBuffer<200> jsonBuffer;
   JsonObject &root = jsonBuffer.parseObject(payload);
   const char *mode = root["mode"];
   if (mode == NULL)
   {
      Serial.println("mode is NULL");
      return -1;
   }
   else if (strcmp(mode, "1") == 0)
   {
      message_pub(SETTING_RESPONE_TOPIC_ID, "1");
      light_on();
   }
   else
   {
      message_pub(SETTING_RESPONE_TOPIC_ID, "mode is unknown");
      light_off();
   }
   return 0;
}

static int params_json_parse(char *payload)
{
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject &root = jsonBuffer.parseObject(payload);
   const char *params = root["params"];
   if (params == NULL)
   {
      Serial.println("params is NULL");
      return -1;
   }
   else if (strcmp(params, "1") == 0)
   {
      message_pub(PARAMS_RESPONE_TOPIC_ID, "1");
   }
   else
   {
      message_pub(PARAMS_RESPONE_TOPIC_ID, "params is unknown");
   }
   return 0;
}

static int esp_info_json_parse(char *payload)
{
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject &root = jsonBuffer.parseObject(payload);
   const char *info = root["info"];
   if (info == NULL)
   {
      Serial.println("info is NULL");
      return -1;
   }
   else if (strcmp(info, "1") == 0)
   {
      message_pub(ESP_INFO_RESPONE_TOPIC_ID, "1");
   }
   else
   {
      message_pub(ESP_INFO_RESPONE_TOPIC_ID, "info is unknown");
   }
   return 0;
}