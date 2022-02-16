#include <Arduino.h>
bool light_status = true;
void light_on(void);
void light_off(void);
void setting_init(void)
{
    Serial.println("setting_init");
    if (light_status)
    {
        Serial.println("light_on");
        light_on();
    }
    else
    {
        Serial.println("light_off");
        light_off();
    }
}
void light_on(void)
{
    Serial.println("light_on");
    light_status = false;
}
void light_off(void)
{
    Serial.println("light_off");
    light_status = true;
}