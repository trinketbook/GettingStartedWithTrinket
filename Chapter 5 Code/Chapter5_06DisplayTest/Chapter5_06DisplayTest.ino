/* Test sketch for Adafruit I2C/SPI LCD backpack and a character display 

  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
*/

#include <TinyWireM.h>         // <1>
#include <TinyLiquidCrystal.h>

TinyLiquidCrystal lcd(0);  // <2>

void setup() {
  lcd.begin(16, 2);    // <3>    
  lcd.setBacklight(HIGH);      
  lcd.print("hello, world!");  
}

void loop() {         // <4>
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000); // print the number of seconds since reset
}
/*
<1> Include the wire library for the ATtiny and the display libraries
<2> Call the display library, default address #0 (backpack pads A0-A2 not jumpered)
<3> The display is initialized as a 2 line, 16 character display (change to suit your display), the backlight is turned on, and the message is written to the first line.
<4> Set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0).
*/
