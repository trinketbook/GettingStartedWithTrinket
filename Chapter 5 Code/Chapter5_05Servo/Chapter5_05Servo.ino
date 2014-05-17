/*******************************************************************
  Servo sketch for Adafruit Trinket. Turn the potentiometer knob
  to set the corresponding position on the servo
  (0 = zero degrees, full = 180 degrees)
 
  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
 
  Required library is the Adafruit_SoftServo library
  available at https://github.com/adafruit/Adafruit_SoftServo
  The standard Arduino IDE servo library will not work with 8 bit
  AVR microcontrollers like Trinket due to differences
  in available timer hardware and programming.
*******************************************************************/

#include <Adafruit_SoftServo.h> 
#define SERVO1PIN 0 // <1>
#define POTPIN 1    // <2>

Adafruit_SoftServo myServo1; //create servo object

void setup() {
  OCR0A = 0xAF;          // <3>
  TIMSK |= _BV(OCIE0A);  
 
  myServo1.attach(SERVO1PIN);  // <4>
  myServo1.write(90);          // <5>
  delay(15);                   // Wait 15ms for servo to reach position
}

void loop() {
  int potValue; // variable to read potentiometer
  int servoPos; // variable to convert voltage on pot to servo position
  potValue=analogRead(POTPIN);  // <6>
  servoPos = map(potValue, 0, 1023, 0, 179);
  myServo1.write(servoPos);     // <7>
  delay(15);    // waits 15ms for servo to reach the position
}

volatile uint8_t counter = 0;  // The timer counter variable

SIGNAL(TIMER0_COMPA_vect) {    // <8>
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}
/*
<1> The servo control wire (usually orange) is connected to Trinket on this pin number (set to Pin #0).
<2> The potentiometer center pin is connected to this pin (set to Trinket Pin #2 which is Analog 1 on the ATtiny85).
<3> These two lines set up the interrupt that will refresh the servo every 20 milliseconds to keep them in the position desired.
<4> This calls the servo library to identify the servo is on SERVO1PIN on Trinket
<5> Set an initial position for the servo (it could be anywhere on power up).
<6> Read voltage on the potentiometer (AnalogRead returns 0 to 1023) and then map the values to a value of 0 to 179 degrees.
<7> This tells the servo to go to position desired.
<8> The built in millis() timer is used to keep track of time, and refresh the servo every 20 milliseconds. The +SIGNAL(TIMER0_COMPA_vect)+ function is the interrupt that will be called by the microcontroller every 2 milliseconds.
*/
