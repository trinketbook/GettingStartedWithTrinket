/* Adafruit Trinket-based Room Occupancy sensor and display 

   From Chapter 6 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version, Phillip Burgess
*/

#include <TinyWireM.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"         // <1>

const int PIRpin = 1;   // <2>
uint8_t pirState = LOW; // Stores state of the PIR sensor

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
 pinMode(PIRpin, INPUT); // Initial state is low
 matrix.begin(0x70);     // pass in the address
}

static const uint8_t PROGMEM // X and square bitmaps <3>

 x_bmp[] =
{ B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001 },

 box_bmp[] =
{ B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111 };

void loop() {
  int sense = digitalRead(PIRpin); // Read PIR Sensor
  if(sense == HIGH)  {           // If high and it was low, sensor tripped
    if(pirState == LOW){         //   and we display a red X
      matrix.clear();
      matrix.drawBitmap(0, 0, x_bmp, 8, 8, LED_RED);
      matrix.writeDisplay();
      pirState = HIGH;
    }
  } else {
    if(pirState == HIGH) {         // If low and state was high, sensor set
      matrix.clear();              // and we display a green box
      matrix.drawBitmap(0, 0, box_bmp, 8, 8, LED_GREEN);
      matrix.writeDisplay();
      pirState = LOW;
    }
  }
}
/*
<1> The Adafruit graphics library adds a great deal of unneeded code but simplifies this simple project significantly.  Using "raw" Wire library calls as in the Trinket Jewelry project would make the code smaller.
<2> PIR signal pin is connected to Trinket Pin #1
<3> These bitmaps may be changed to any design desired.
*/