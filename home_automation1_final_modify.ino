#include <SoftwareSerial.h>

int in1 = 9;
int sensor = 8;
int led = 13;
unsigned long t1 = 0, t2 = 0;
int state = HIGH;

int TX = 10;
int RX = 11;

char data = 'L', mode = 'A';
SoftwareSerial bluetooth(TX, RX);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(led, HIGH);
}

void loop() {

  if (bluetooth.available()) {
    data = bluetooth.read();           // if blutooth device is on than take input(mode information)
    if (data == 'M' || data == 'A') {  //M->manual mode && A -> automated mode
      mode = data;
    }
  }

  if (mode == 'A') {
    if (digitalRead(sensor) == HIGH) {  //if motion is detected
      state = HIGH;
      //digitalWrite(led, LOW);
      t1 = millis();
    } else {
      t2 = millis();
      //digitalWrite(led, HIGH);
      if (abs(t2 - t1) > 10000)
        state = LOW;
    }
    digitalWrite(in1, state);
  }

  else if (mode == 'M') {
    if (data == 'L') {
      digitalWrite(in1, LOW);
    } else if (data == 'l') {
      digitalWrite(in1, HIGH);
    }
  }
}
