

int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int a[6];
unsigned long delta;


void setup() {
  Serial.begin(115200);
}


void loop() {
  delta = micros();
  
  for(int i=0; i<6; i++) {
    a[i] = analogRead(analogPins[i]);

  }
  delta = micros() - delta;
  if(delta > 740)
  Serial.println(delta);

}