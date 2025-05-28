int in1 = 9;
int sensor = 8;
int led = 13;
unsigned long t1 = 0, t2 = 0;
int state = 1;
void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(led, HIGH);
}

void loop() {
  if (digitalRead(sensor) == HIGH) {
    state = 1;
    digitalWrite(led, LOW);
    t1 = millis();  //time read as miliseconds
  } else {
    t2 = millis(); 
    digitalWrite(led, HIGH);  //turning on device
    if ((t2 - t1) > 10000) {  //time difference
      state = 0;
    }
  }

  if (state == 0) {
    digitalWrite(in1, HIGH);
  } else if (state == 1) {
    digitalWrite(in1, LOW);
  }
}
