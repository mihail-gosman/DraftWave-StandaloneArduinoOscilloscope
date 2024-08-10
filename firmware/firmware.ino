void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  long a = millis();
  //Serial.println(analogRead(A0));
  a = millis() - a;
  Serial.println(a);
}
