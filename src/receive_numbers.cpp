#include <Arduino.h>
#include <ArduinoJson.h>
#include <Servo.h>
#include <math.h>
#include <HUSKYLENS.h>
#include <SoftwareSerial.h>

#include <color.h>

#define slave1_pin1 2
#define slave1_pin2 3
#define slave1_pin3 4
#define slave1_pin4 5
#define slave1_pin5 6
#define slave1_pin6 7
#define slave1_pin7 8
#define slave2_pin1 38
#define slave2_pin2 36
#define slave2_pin3 34
#define slave2_pin4 32
#define slave2_pin5 30
#define slave2_pin6 28
#define slave2_pin7 26
#define slave3_pin1 53
#define slave3_pin2 51
#define slave3_pin3 49
#define slave3_pin4 47
#define slave3_pin5 45
#define slave3_pin6 43
#define slave3_pin7 41
#define wheel_servo_pin 9
#define motor_pin 10

#define led_alert 13


HUSKYLENS ai_lens;
SoftwareSerial lens_serial(52, 50);
StaticJsonDocument<200> input_report;
Servo wheel_servo;

int left_distance = 0;
int right_distance = 0;
int forward_distance = 0;

int servo_degree = 90;
int servo_min = 30;
int servo_max = 140;

int current_turn = 1;
bool is_turning = false;


int limit_servo(int degree_to_change) {

    if (degree_to_change <= servo_min) {
        return servo_min;
    } else if (degree_to_change >= servo_max) {
        return servo_max;
    } else {
        return degree_to_change;
    }
}

int read_distance(int slave_num) {
    int num_to_receive = 0;

    int selected_slave_pin1;
    int selected_slave_pin2;
    int selected_slave_pin3;
    int selected_slave_pin4;
    int selected_slave_pin5;
    int selected_slave_pin6;
    int selected_slave_pin7;
    if (slave_num == 1) {
        selected_slave_pin1 = slave1_pin1;
        selected_slave_pin2 = slave1_pin2;
        selected_slave_pin3 = slave1_pin3;
        selected_slave_pin4 = slave1_pin4;
        selected_slave_pin5 = slave1_pin5;
        selected_slave_pin6 = slave1_pin6;
        selected_slave_pin7 = slave1_pin7;
    } else if (slave_num == 2) {
        selected_slave_pin1 = slave2_pin1;
        selected_slave_pin2 = slave2_pin2;
        selected_slave_pin3 = slave2_pin3;
        selected_slave_pin4 = slave2_pin4;
        selected_slave_pin5 = slave2_pin5;
        selected_slave_pin6 = slave2_pin6;
        selected_slave_pin7 = slave2_pin7;
    } else if (slave_num == 3) {
        selected_slave_pin1 = slave3_pin1;
        selected_slave_pin2 = slave3_pin2;
        selected_slave_pin3 = slave3_pin3;
        selected_slave_pin4 = slave3_pin4;
        selected_slave_pin5 = slave3_pin5;
        selected_slave_pin6 = slave3_pin6;
        selected_slave_pin7 = slave3_pin7;
    }

    int num_index = 0;
    int pin_list[7] = {selected_slave_pin1, selected_slave_pin2, selected_slave_pin3, selected_slave_pin4, selected_slave_pin5, selected_slave_pin6, selected_slave_pin7};
    for (int cur_pin : pin_list) {
        num_to_receive += digitalRead(cur_pin)*pow(2, num_index);
        num_index++;
    }

    return num_to_receive;
}

void setup() {
    pinMode(slave1_pin1, INPUT);
    pinMode(slave1_pin2, INPUT);
    pinMode(slave1_pin3, INPUT);
    pinMode(slave1_pin4, INPUT);
    pinMode(slave1_pin5, INPUT);
    pinMode(slave1_pin6, INPUT);
    pinMode(slave1_pin7, INPUT);
    pinMode(slave2_pin1, INPUT);
    pinMode(slave2_pin2, INPUT);
    pinMode(slave2_pin3, INPUT);
    pinMode(slave2_pin4, INPUT);
    pinMode(slave2_pin5, INPUT);
    pinMode(slave2_pin6, INPUT);
    pinMode(slave2_pin7, INPUT);
    pinMode(motor_pin, OUTPUT);
    digitalWrite(motor_pin, HIGH);
    COLOR_set_sensor(A0, A1, A3, A4, 11);
    COLOR_init();
    wheel_servo.attach(wheel_servo_pin);
    Serial.begin(115200);
    lens_serial.begin(9600);
    while (!ai_lens.begin(lens_serial)) {
        Serial.println("he can't KEEP GETTING AWAY WITH THIS!");
    }
}

void loop() {
    right_distance = read_distance(1);
    left_distance = read_distance(2);
    forward_distance = read_distance(3);
    // if (Serial.availableForWrite() > 0) {
    //     Serial.print("forward distance: ");
    //     Serial.print(forward_distance);
    //     Serial.print(",    left distace: ");
    //     Serial.print(left_distance);
    //     Serial.print(",    right distance: ");
    //     Serial.print(right_distance);
    //     Serial.print(",    red color: ");
    //     Serial.println(COLOR_get_red());
    //     Serial.print(",    green color: ");
    //     Serial.println(COLOR_get_green());
    //     Serial.print(",    blue color: ");
    //     Serial.println(COLOR_get_blue());
    // }

    // if (Serial.available() > 0) {
    //     deserializeJson(input_report, Serial);

    //     servo_degree = limit_servo(input_report["servo"]);
    // }

    // if ()
    // if (right_distance <= 10 && (right_distance == 122 || right_distance == 0)) {
    //     servo_degree = limit_servo(83 - map(right_distance, 10, 0, 0, 28));
    // } else if (left_distance <= 10 && (left_distance == 122 || left_distance == 0)) {
    //     servo_degree = limit_servo(83 + map(right_distance, 10, 0, 0, 28));
    // } else {
    //     servo_degree = 83;
    // }
    
    if (!ai_lens.available()) {
        // wheel_servo.write(66);
        // delay(400);
        // wheel_servo.write(77);
        Serial.println("failed");
    }
    while (ai_lens.available()) {
        HUSKYLENSResult result = ai_lens.read();
        switch (result.ID) {
            case 1:
                wheel_servo.write(66);
                Serial.println("ez");
                delay(250);
                break;

            case 2:
                wheel_servo.write(112);
                Serial.println("ez");
                delay(250);

        }
    }

    // if (COLOR_get_green() >= 280) {
    //     servo_degree = 140;
    //     wheel_servo.write(servo_degree);
    //     delay(330);
    //     current_turn++;
    // } else {
    //     servo_degree = 83;
    // }

    // if (current_turn >= 4) {
    //     digitalWrite(motor_pin, LOW);
    // }

    // wheel_servo.write(servo_degree);
}