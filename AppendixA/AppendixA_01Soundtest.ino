/* Trinket Animal - Sound testing module

   PLEASE NOTE: Works on Arduino Uno, Leonardo, Mega, etc.
   This can work on Trinket with right pin changes and an FTDI Friend
   
   From Appendix A of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
   Version 1.01 - Move to Appendix A for final release
*/
#define SPEAKER 11 // Piezo Speaker pin (positive lead)
                   // For Trinket, change to 2
#define POT A0     // for Trinket, use 1 for Pin #2 (not A1)
//#include <SoftwareSerial.h>
//SoftwareSerial Serial(1,0); // If Trinket, serial out Pin #0 

void setup() {
  Serial.begin(9600);
  pinMode(SPEAKER,OUTPUT); // important to set pin as output
}

void loop() {  // <1>
  chirp();  delay(2000);
  meow();   delay(2000);
  meow2();  delay(2000);
  mew();    delay(2000);
  ruff();   delay(2000);
  arf();    delay(2000);
  hoot();   delay(2000);
// varyFrequency(); // <2>
// scale();         // Plays a tone scale
}

void varyFrequency() {
// use potentiometer to produce one tone per value of pot
// good for getting pitch value to use in making sound routines

  int reading;
  const uint8_t scale = 1; // 1 for high frequencies, scale up to 15 for
                           //   lowest freqs
  reading = scale * analogRead(POT); // <3>
  playTone(reading, 1000);
  Serial.print("Freq = ");
  Serial.println(reading);
}

void chirp() {             // Bird chirp
  for(uint8_t i=200; i>180; i--)
     playTone(i,9);
}

void meow() {              // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(5100,50);       // "m" (short)
  playTone(394,180);       // "eee" (long)
  for(i=990; i<1022; i+=2) // vary "ooo" down
    playTone(i,8);
  playTone(5100,40);       // "w" (short)
}

void meow2() {             // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
    playTone(i,10);
  playTone(5100,40);       // "w" (short)
}

void mew() {               // cat mew
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w" (short)
}

void ruff() {              // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2) // "rrr" (vary down)
    playTone(i,3);
  playTone(1664,150);     // "uuu" (hard to do)
  playTone(12200,70);     // "ff" (long, hard to do)
}

void arf() {              // dog arf
  uint16_t i;
  playTone(890,25);       // "a" (short)
  for(i=890; i<910; i+=2) // "rrr" (vary down)
    playTone(i,5);
  playTone(4545,80);      // intermediate
  playTone(12200,70);     // "ff" (shorter, hard to do)
}

void hoot() {                  // owl hoot (fairly mechanical. . .)
  uint16_t i;
  playTone(50,2);              // short low to make "h" (hard to do)
  for(i=0; i<240; i=i+2) {     // oooo sound (vary tones slightly
    if(i%2) playTone(1832, 2); // every 2 ms to soften)
    else playTone(1800, 2);
  }
  playTone(1790,10);           // bring up slightly near end
  playTone(14000,3);           // next 6 to simulate a t which is
  delay(2);                    // again a hard sound to do
  playTone(14000,3);
  delay(2);
  playTone(14000,3);
}

void playTone(uint16_t tone1, uint16_t duration) { // <4>
  if(tone1 < 50 || tone1 > 15000) return; // these do not play on
                                          // our piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(tone1);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(tone1);
  }
}

void scale() {                 // Play different frequencies in sequence
  for(uint16_t i=50; i<15000; i++) {
    playTone(i,20);
  }
}
/*
<1> Currently the loop function plays the different premade animal sounds.  
For making a new sound, comment out the animal functions.
<2> Use the varyFrequency function to set a tone you might wish to use. 
<3> analogRead produces values from 0 to 1023.  To get tones from 0 to 
2047, change SCALE to 1, to get 0 to 3071 change to 2, etc.  This provides 
a bit more granularity at lower frequencies.
<4> Function +playTone+ plays a tone on a piezo speaker. Shorter values 
produce higher frequencies which is opposite beep() but avoids some math 
delay (long math and divide). Similar to code by Erin Robotgrrl.
*/
