int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int analogReadings[6];  
volatile unsigned long delta;  // Mark as volatile since it is used in ISR
volatile int data = 0;         // Mark as volatile to safely access in both ISR and loop

void readAnalogValues() {
  for(int i = 0; i < 6; i++) {
    analogReadings[i] = analogRead(analogPins[i]);
  }
}

void sendAnalogValues() {
  for (int i = 0; i < 6; i++) {
    Serial.println(analogReadings[i]);
  }
}

ISR(TIMER2_OVF_vect) {
  delta = micros();         // Update delta
  readAnalogValues();       // Read analog values
  data = 1;                 // Set flag to send data in loop
  TCNT2 = 6;                // Reset timer count
}

void timerInit() {
  noInterrupts();           // Disable interrupts during timer setup
  TCCR2A = 0;               // Clear Timer2 control registers
  TCCR2B = 0;
  TCCR2B |= (1 << CS22);    // Set prescaler to 64
  TIMSK2 |= (1 << TOIE2);   // Enable Timer2 overflow interrupt
  TCNT2 = 6;                // Load initial value for Timer2 counter
  interrupts();             // Re-enable interrupts
}

void setup() {
  Serial.begin(115200);     // Initialize Serial communication
  for(int i = 0; i < 6; i++) {
    pinMode(analogPins[i], INPUT);  // Set analog pins as inputs
  }
  delta = micros();         // Initialize delta before starting timer
  timerInit();              // Initialize Timer2
}

void loop() {
  if(data) {                // Check if data flag is set
    Serial.println("\nTime elapsed:");
    Serial.println(delta);  // Print the time delta
    sendAnalogValues();     // Send the analog values to Serial
    data = 0;               // Clear the data flag
  }
}
