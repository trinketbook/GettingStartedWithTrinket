/* Trinket Theremin
Read the voltage from a Cadmium Sulfide (CdS) photocell voltage divider and output a corresponding tone to a piezo buzzer
*/

#define SPEAKER   0 // Speaker on Trinket Pin #0  
#define PHOTOCELL 1 // CdS photocell on Trinket Pin #2 (Analog Pin 1) 
#define SCALE     2 // You can change this to change the tone scale

void setup() { 
  pinMode(SPEAKER,OUTPUT); // <1>
 }

void loop() { 
  int reading=analogRead(PHOTOCELL); // <2>
                                    
  int freq=220+(int)(reading*SCALE); // <3>
  beep(SPEAKER,freq,400);    // <4>
  delay(50);                 // <5>
 }

// the sound producing function <6>
void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) {
  int x;
  long delayAmount = (long)(1000000/frequencyInHertz); 
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2)); 
  for (x=0; x<loopTime; x++) {
     digitalWrite(speakerPin,HIGH); 
     delayMicroseconds(delayAmount); 
     digitalWrite(speakerPin,LOW);
     delayMicroseconds(delayAmount); 
  }
}
/*
<1> It is important to set the speaker pin for digital output.  If this is not done, an oscilloscope will see the pin change frequency but current will not flow to the piezo.
<2> The voltage proportional to the light hitting the photocell is read on Analog pin 1 which is Trinket Pin #2 per the diagram in <<chap-introduction>>.
<3> The analog value is scaled to to start at 220 Hz and rise based on the voltage multiplied by a value in SCALE that the programmer may change as desired in the code.
<4> The Arduino +tone+ function does not work for the ATtiny85 on the Trinket.  The +beep+ function is similar and will work for any Trinket data pin.  The duration is selected to be 400 milliseconds, this may be changed in the code also.
<5> The delay value (in milliseconds) also is not critical and may be changed.
<6> The beep code is similar to that from Dr. Leah Buechley at http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
*/