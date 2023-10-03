#include <Arduino.h>
#include <math.h>
#include <Wire.h>

bool is_led_on = true;


void send_data(int bytes) {
    // char data_to_send[20];
    // sprintf(data_to_send, "%d", min(450, 1000));
    Wire.write(3);
    delay(170);
}


void setup() {
    Wire.begin(8);
    Wire.onReceive(send_data);
}

void loop() {
}