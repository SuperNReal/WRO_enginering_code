#include <Arduino.h>
#include <Wire.h>

#define led_data 13
#define led_bad 3

// Include the required Wire library for I2C<br>#include <Wire.h>
int x = 0;
void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
  Serial.print("received: ");
  Serial.println(x);
}
void setup() {
  // Define the led_data pin as Output
  pinMode (led_data, OUTPUT);
  pinMode(led_bad, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  Serial.begin(9600);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void loop() {
  //If value received is 0 blink led_data for 200 ms
  if (x == '0') {
    digitalWrite(led_data, HIGH);
    delay(200);
    digitalWrite(led_data, LOW);
    delay(200);
  }
  //If value received is 3 blink led_data for 400 ms
  else if (x == '3') {
    digitalWrite(led_data, HIGH);
    delay(400);
    digitalWrite(led_data, LOW);
    delay(400);
  }

  else {
    digitalWrite(led_bad, HIGH);
    delay(500);
    digitalWrite(led_bad, LOW);
    delay(500);
  }
}