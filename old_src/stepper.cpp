#include <Arduino.h>
#include <ArduinoJson.h>
#include <Stepper.h>

#define stepsPerRevolution 2038
#define led_status_pin 12

StaticJsonDocument<200> input_report;
Stepper the_stepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

int speed_stepper = 13;
int steps = 1;
bool is_connected = false;


void setup() {
  pinMode(led_status_pin, OUTPUT);
  Serial.begin(9600);
	the_stepper.step(stepsPerRevolution);
}

void loop() {
  if (Serial.available() > 0) {
    is_connected = true;
    deserializeJson(input_report, Serial);

    speed_stepper = input_report["speed"];
    steps = input_report["steps"];
  } else {
    is_connected = false;
  }
  
  
  digitalWrite(led_status_pin, is_connected);
	the_stepper.setSpeed(speed_stepper);
  the_stepper.step(steps);
  // delay(110);
  // the_stepper.setSpeed(speed_stepper);
  // the_stepper.step(-255);
  // delay(110);
}