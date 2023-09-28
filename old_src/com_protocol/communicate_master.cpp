#include <Arduino.h>
#include <Wire.h>


String UNO_receive(int address, int bytes_to_read) {
    String received_data = "";
    
    Wire.requestFrom(address, bytes_to_read);
    while (Wire.available()) {
        char letter = Wire.read();
        received_data += letter;
    }

    return received_data;
}


String distance;


void setup() {
    Wire.begin();
    Serial.begin(9600);
}

void loop() {

    distance = UNO_receive(8, 4);
    if (distance.length() > 0) {
        Serial.println(distance);
    }

    delay(500);

}