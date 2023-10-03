#include <Arduino.h>

int analog_value = 0;


void setup() {
    pinMode(A3, INPUT);
    Serial.begin(9600);
}

void loop() {
    analog_value = analogRead(A3);
    
    Serial.print(analog_value);
    Serial.print(" ");
    
    if (analog_value <= 280) {
        Serial.println("low");
    } else {
        Serial.println("can we get much higher");
    }
}