int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int analogReadings[6];
volatile bool sendDataFlag = false;  // Flag to indicate when to send data
unsigned long delta = micros();


void timerInit() {
  // Set up Timer2
  TCCR2A = 0;  // Clear Control Register A
  TCCR2B = 0;  // Clear Control Register B

  TCCR2B |= (1 << CS22) | (1 << CS21);  // Set prescaler to 64
  TIMSK2 |= (1 << TOIE2);  // Enable Timer2 overflow interrupt
  TCNT2 = 5;  // Preload the timer
}


void readAllAnalogPins() {
  for (int i = 0; i < 6; i++) {
    analogReadings[i] = analogRead(analogPins[i]);
  }
}


void sendAnalogData() {
  for (int i = 0; i < 6; i++) {
    Serial.write(analogReadings[i]);
  }
 // Serial.println();  // Print a newline after sending data
}


ISR(TIMER2_OVF_vect) {
  readAllAnalogPins();  // Read all analog pins
  sendDataFlag = true;  // Set the flag to send data in the loop
  TCNT2 = 5;  // Reset the timer preload value
  
  // Calculate delta time
  delta = millis() - delta;
  // Set delta for output in the main loop
}


void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud
  timerInit();  // Initialize Timer2
}


void loop() {
   if (sendDataFlag) {
    sendAnalogData();  // Send data only when the flag is set
    sendDataFlag = false;  // Reset the flag after sending data
    
    // Send delta time since last reading
    Serial.print("Delta time: ");
    Serial.println(delta);
    
    delta = millis();  // Reset delta timer
  }
  while (Serial.availableForWrite()<=40) {
  ;
  };
}
