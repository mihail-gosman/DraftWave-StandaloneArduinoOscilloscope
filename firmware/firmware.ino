unsigned long delta = millis();
int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int analogInput[6];

void startMeasurement() {
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << TOIE1);
}

void stopMeasurement() {
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << TOIE1);
}

void setup() {
  Serial.begin(115200);
  
  TCCR1A = 0;
  TCCR1B = 0;
  
  for (int i=0; i<6; i++) {
    pinMode(analogPins[i], INPUT);
  }  
}

ISR(TIMER1_OVF_vect) {
  for (int i=0; i<6; i++) {
    analogInput[i] = analogRead(analogPins[i]);
  }

  for (int i=0; i<6; i++) {
    Serial.println(analogInput[i]);
  }
  Serial.println(" ");
}

void loop() {
  

}