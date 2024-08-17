void setup() {
  DDRB = 0xFF;
  DDRD = 0x00;
  PORTD = 0xFF;
}

void loop() {
  PORTB ^= 0xFF;

  while ((PIND & 0xFF) != 0b11111011) {
  }

  PORTB = 0b10101010;

  while ((PIND & 0xFF) != 0b11110111) {
  }

  for (uint8_t i = 0; i < 8; i++) {
    PORTB = (1 << i);
    delay(100);
  }

  PORTB ^= 0xFF;
  delay(1000);

  for (uint8_t i = 0; i < 8; i++) {
    PORTB = (PORTB << 1) | (PORTB >> 7);
    delay(100);
  }

  PORTB = 0x00;
}
