/* Functions which set up PWM on Trinket Pin #4 using ATtiny85 Timer 1

  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
*/
void PWM4_init() {              // Call this function in setup
  TCCR1 = _BV (CS10);                  // no prescaler
  GTCCR = _BV (COM1B1) | _BV (PWM1B);  // clear OC1B on compare
  OCR1B = 127;                  // duty cycle initialize to 50%
  OCR1C = 255;                  // frequency
}

// Function to use an analogWrite type function for Trinket Pin #4
void analogWrite4(uint8_t duty_value) {
  OCR1B = duty_value; // duty may be 0 to 255 (0 to 100%)
}
