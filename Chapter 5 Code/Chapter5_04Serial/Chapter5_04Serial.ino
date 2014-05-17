/* Trinket Software Serial Echo Program 

   From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/

#include <SoftwareSerial.h> // Use the Arduino IDE library
#include <ctype.h>          // <1>

SoftwareSerial Serial(2,0); // <2>

#define LED 1  // <3>

void setup(void) {
  Serial.begin(9600); // <4>
  Serial.println("Hello from Trinket");  // Verify comms working
  Serial.println(" ");
  Serial.println("Type text and I will echo it back");
  Serial.println("Any time I see a number, I will flash the LED");
  Serial.println(" ");
  pinMode(LED, OUTPUT);  // Red LED pin
}

void loop(void) {  // <5>
  char c;
  if (Serial.available()) {   // Has something been received?
    c = Serial.read();        //  yes, read it
    Serial.write(toupper(c)); // write it back out
    if(c >= '0' and c <= '9') flash();  // if a number, flash the LED
  }
}

void flash() {
  digitalWrite(LED, HIGH);   // <6>
  delay(500);
  digitalWrite(LED, LOW);
}
/*
<1> This is the standard C library for character functions.
<2> Sefine a software serial connection, the pin order is important: first is the receive pin 2 (abbreviated RX), the second the transmit pin 0 (TX).  Both values are required, if you want to only send, use the SendOnlySoftwareSerial library.
<3> The program uses the Trinket on-board LED on Pin #1.
<4> Start the serial connection - be sure you set up the computer terminal program for 9600 baud, 8 bits, 1 stop bit, no parity (a fairly standard set of values).
<5> If a character is typed on the computer, it is changed to upper case and sent back to the user.  If a number is types, the LED is flashed.
<6> This function flashes the LED for half a second as an indicator.
*/