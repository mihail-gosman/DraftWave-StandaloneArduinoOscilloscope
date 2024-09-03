#define 

unsigned long delta = millis();
int analogPins[] = { A0, A1, A2, A3, A4, A5 };
int analogInput[6];
char incomingByte;

void startMeasurement() {
  TIMSK1 |= (1 << TOIE1);         // Enable Timer1 overflow interrupt to start measurements
}

void stopMeasurement() {
  TIMSK1 &= ~(1 << TOIE1);        // Disable Timer1 overflow interrupt to stop measurements
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


void setup() {
 Serial.begin(115200);       

  TCCR1A = 0;                     // Clear Timer1 control registers
  TCCR1B = 0;                     
  TCCR1B |= (1 << CS10);          // Set Timer1 prescaler to 1 (no prescaling)

  for (int i = 0; i < 6; i++) {
    pinMode(analogPins[i], INPUT);  // Set analog pins as input
  } 
}


void loop() {
  while (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == '\n') {
      break;
    }
    else {
      if (incomingByte == 'A'){
        startMeasurement();
      }
      else {
        stopMeasurement();
      }
    }

  }
}