/*
 Blink for Trinket (ATtiny85 board by Adafruit Industries)
   Turns on an LED on for one half second, then off for one half second, repeatedly.
   
   To upload to your Trinket:
   1) Select the proper board from the Tools->Board Menu
   2) Select USBtinyISP from the Tools->Programmer
   3) Plug in the Trinket, make sure you see the green LED lit
   4) Press the button on the Trinket - verify you see
      the red LED pulse. This means it is ready to receive data
   5) Click the IDE upload button above within 10 seconds
   
From Chapter 3 of Getting Started with Trinket by Mike Barela, 2014  
Version 1.0 - Initial Version
*/
int led = 1;    // <1>
  
void setup() {  // <2>
  pinMode(led, OUTPUT); // <3>
}
 
void loop() {   // <4>
  digitalWrite(led, HIGH); // <5>
  delay(500);   // <6>
  digitalWrite(led, LOW);  // <7>
  delay(500);   // <8>
}
/*
<1> Define which digital pin to write to.  For Trinket this would be Pin #1, which is connected to the on-board red LED.  
<2> The setup routine runs once when you power on or press the Reset button.
<3> This command sets the LED pin (#1) as an output.
<4> The loop routine runs over and over again.  
<5> Setting the LED pin as HIGH turns on the current to the LED, lighting it up
<6> The +delay+ function delays the number of milliseconds (thousandths of a second).  In each delay, we wait 500 milliseconds whichg is half a second.
<7> Setting the LED pin as LOW turns it off.
<8> Blinking the LED twice a second helps distinguish this program from the once a second flash when the bootloader runs.
*/
