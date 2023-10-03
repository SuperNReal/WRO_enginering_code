#include <Arduino.h>
#include <color.h>


/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/
int S0;
int S1;
int S2;
int S3;
int sensorOut;


void COLOR_init() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  //%20 frequency
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}


void COLOR_set_sensor(int s0, int s1, int s2, int s3, int sensor_out) {
  S0 = s0;
  S1 = s1;
  S2 = s2;
  S3 = s3;
  sensorOut = sensor_out;
}


int COLOR_get_red() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int redFrequency = pulseIn(sensorOut, LOW);
  return redFrequency;
}

int COLOR_get_green() {
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int greenFrequency = pulseIn(sensorOut, LOW);
  return greenFrequency;
}

int COLOR_get_blue() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int blueFrequency = pulseIn(sensorOut, LOW);
  return blueFrequency;
}