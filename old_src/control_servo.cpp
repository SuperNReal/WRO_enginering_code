#include <Arduino.h>
#include <ArduinoJson.h>
#include <Servo.h>

StaticJsonDocument<200> input_report;
Servo servo_bro;

const int delay_time = 300;

int servo_degree = 90;
int servo_min = 60;
int servo_max = 100;


int limit_servo(int degree_to_change) {

    if (degree_to_change <= servo_min) {
        return servo_min;
    } else if (degree_to_change >= servo_max) {
        return servo_max;
    } else {
        return degree_to_change;
    }
}

void setup() {
    servo_bro.attach(8);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        deserializeJson(input_report, Serial);

        servo_degree = limit_servo(input_report["servo"]);
    }
    
    servo_bro.write(servo_degree);
}