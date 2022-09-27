#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
}

#define TIMEOUT 100

void loop()
{
    char message[128];
    uint8_t idx = 0;
    uint32_t receive_time = 0;
    bool receiving = false;

    memset(message, 0, sizeof(message));

    while (true)
    {
        while (Serial.available())
        {
            if (idx == 0)
            {
                receiving = true;
                receive_time = millis();
            }

            message[idx++] = Serial.read();
        }

        if ((strlen(message) > 0) && !receiving)
        {
            Serial.println(message);
            memset(message, 0, sizeof(message));
            idx = 0;
        }

        if ((millis() - receive_time) > TIMEOUT)
            receiving = false;

    }
}