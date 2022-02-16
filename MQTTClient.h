#ifndef _MQTTCLIENT_h
#ifdef __cplusplus
#endif
#define _MQTTCLIENT_h
#define MAX_TOPIC_NAME_LENGTH 64
#include <stdint.h>

typedef enum
{
    REALTIME_TOPIC_ID = 0,
    SETTING_TOPIC_ID,
    SETTING_RESPONE_TOPIC_ID,

    PARAMS_TOPIC_ID,
    PARAMS_RESPONE_TOPIC_ID,

    ESP_INFO_TOPIC_ID,
    ESP_INFO_RESPONE_TOPIC_ID,

    MAX_MESSAGE_PUB_SUB // NOT A TOPIC ID
} MQTT_CONNECTION_ID;

typedef struct
{
    uint16_t topic_id;
    char topic_name[50];
} MQTT_CONNECTION_ID_INFO;
void mqtt_init(void);
void client_loop(void);
void real_time_update(void);
void message_pub(MQTT_CONNECTION_ID topic_id, const char *payload);
#endif