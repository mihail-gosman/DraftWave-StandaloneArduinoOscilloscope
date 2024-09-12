
int analogPins[] = { A0, A1, A2, A3, A4, A5 };
uint16_t analogReadings[5];
unsigned long delta;


void readAllAnalogPins() {
  for(int i=0; i<6; i++) {
    analogReadings[i] = analogRead(analogPins[i]);
  }
}


void sendAnalogData() {
  for(int i=0; i<6; i++) {
    int value = analogReadings[i];
    Serial.write(value);
  }
}

void setup() {
  Serial.begin(115200);

}


void loop() {
  delta = millis();
  //readAllAnalogPins();
  analogReadings[1] = 30;
  sendAnalogData();

  delta = millis() - delta;
  
  Serial.println(delta);

}