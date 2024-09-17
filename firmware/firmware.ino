

int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int analogReadings[5];
unsigned long delta;


void readAllAnalogPins() {
  for(int i=0; i<6; i++) {
    analogReadings[i] = analogRead(analogPins[i]);
  }
}


void sendAnalogData() {
  for(int i=0; i<6; i++) {
    Serial.write((byte*)&analogReadings[i], sizeof(analogReadings[i]));
  }

  
  Serial.write("\n");
}

void setup() {
  Serial.begin(115200);

}


void loop() {
  delta = millis();
  readAllAnalogPins();
  sendAnalogData();
  delay(1);
  delta = millis() - delta;
  //Serial.println(Serial.availableForWrite());
  //while (Serial.availableForWrite() < 7);
  //Serial.println(delta);
  
}