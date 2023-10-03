#include <Arduino.h>

#define ultra1_pin A5


void setup() {
    pinMode(ultra1_pin, INPUT);
    Serial.begin(9600);

}

void loop() {
    Serial.println(analogRead(ultra1_pin));
}