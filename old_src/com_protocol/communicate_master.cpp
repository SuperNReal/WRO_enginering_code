#include <Arduino.h>
#include <Wire.h>


char translate_number(char num) {
    if (num == 0) {
        return '0';
    } else if (num == 1) {
        return '1';
    } else if (num == 2) {
        return '2';
    } else if (num == 3) {
        return '3';
    } else if (num == 4) {
        return '4';
    } else if (num == 5) {
        return '5';
    } else if (num == 6) {
        return '6';
    } else if (num == 7) {
        return '7';
    } else if (num == 8) {
        return '8';
    } else if (num == 9) {
        return '9';
    }
}


String UNO_receive(int address, int bytes_to_read) {
    String received_data = "";
    
    Wire.requestFrom(address, bytes_to_read);
    Serial.print("received: ");
    while (Wire.available()) {
        char letter = Wire.read();
        Serial.print(letter);
        Serial.print(translate_number(letter));
    }
    Serial.println();

    return received_data;
}


String distance;


void setup() {
    Wire.begin();
    Serial.begin(9600);
}

void loop() {

    distance = UNO_receive(8, 1);
    if (distance.length() > 0) {
        // Serial.println(distance);
    }

    delay(500);

}