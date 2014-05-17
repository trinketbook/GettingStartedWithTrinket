/*  Trinket Animal  

   From Chapter 6 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/
#include <Adafruit_SoftServo.h> // SoftwareServo (works on non PWM pins)

#define SERVO1PIN 0     // Servo control line (orange) on Trinket Pin #0
#define SPEAKER   1     // Piezo Speaker on Pin #1
#define PHOTOCELL 1     // CdS photocell on Pin #2 (Analog Pin 1)

Adafruit_SoftServo myServo1; // create servo object
int16_t servoPosition;       // servo position

void setup() {
  OCR0A = 0xAF;         // <1>
  TIMSK |= _BV(OCIE0A); 

  servoPosition = 90;            // Tell servo to go to midway
  myServo1.attach(SERVO1PIN);    // Attach the servo to pin 0 on Trinket
  myServo1.write(servoPosition); // and move servo
  delay(15);               // Wait 15ms for servo to reach the position
  pinMode(SPEAKER,OUTPUT); // <2>
}

void loop() {
  uint16_t light_reading; 
  if(servoPosition != 0)  // <3>
    servoPosition = 0;    // if it's up, go down & vice versa
  else
    servoPosition = 180;
  light_reading = analogRead(PHOTOCELL); // <4>                                         
  if(light_reading < 800) { // if the photocell is dark, we're petting
    chirp();                //   the animal, so make sound ...
    myServo1.write(servoPosition); // and tell servo to move
  }
  delay(1000); // wait between chirps (can be changed)
}

void chirp() {  // Generate the Bird Chirp sound
  for(uint8_t i=200; i>180; i--)
  playTone(i,9);
}

void playTone(int16_t tonevalue, int duration) {  // <5>
  for (long i = 0; i < duration * 1000L; i += tonevalue * 2) {
    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(tonevalue);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(tonevalue);
  }
}

volatile uint8_t counter = 0;  // <6>
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}
/*
<1> This code sets up the servo reffresh timer
<2> Forgetting to set the speaker as an output makes the sound not come out
<3> The servo position is changed every loop but only written if petting animal.
<4> Read the photocell, if the light is below a certain value, something is 
blocking it and this is how we determine the animal is being petted.
<5> Toggles a pin to play a tone on a piezo speaker
<6> This routine refreshes the servos every 20 milliseconds as required.
*/