#include <Arduino.h>
#include <math.h>
#include <Wire.h>

#define led_pin 2

bool is_led_on = true;


void send_data(int bytes) {
    // char data_to_send[20];
    // sprintf(data_to_send, "%d", min(450, 1000));
    Wire.write("wtf0");
}


void setup() {
    pinMode(led_pin, OUTPUT);
    Wire.begin(8);
    Wire.onReceive(send_data);
}

void loop() {
    digitalWrite(led_pin, is_led_on);
    delay(100);
    is_led_on = !is_led_on;
}