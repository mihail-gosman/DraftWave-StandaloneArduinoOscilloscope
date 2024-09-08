

int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int a[6];
int count = 0;
unsigned long delta;
int analogInputs[6];


void timerInit() {
  TCCR2A = 0;
  TCCR2B = 0;
  
  TCCR2B |= (1 << CS21);
  TIMSK2 |= (1 << TOIE2);
  TCNT2 = 0;
  Serial.println("lma");
}


ISR(TIMER2_OVF_vect) {
  delta = micros() - delta;
  
  for(int i=0; i<7; i++){
    analogInputs[i] = analogRead(analogPins[i]);
    Serial.println(analogInputs[i]);
  }
  Serial.println("_______");
  Serial.println(delta);
  
  delta = micros();
}


void setup() {
  Serial.begin(115200);
  timerInit();
}


void loop() {  
  /*for(int i=0; i<1; i++) {
    a[i] = analogRead(analogPins[i]);

  }*/


}