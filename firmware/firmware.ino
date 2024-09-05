

void interruptSetup() {
  TCCR2A = 0;
  TCCR2B = 0;

  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << TOIE2);

  TCNT2 = 0;
  
}

ISR(TIMER2_OVF_vect) {
  Serial.println(micros());
}


void setup() {
  Serial.begin(115200);

  interruptSetup();

}


void loop() {
  ;
}