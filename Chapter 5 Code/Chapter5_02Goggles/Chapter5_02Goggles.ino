/* Low power NeoPixel goggles example
   Makes a nice blinky display with just a few LEDs on at any time.
   
   From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version, Phillip Burgess
*/
#include <Adafruit_NeoPixel.h>  // <1>

#define PIN 0        // Neopixel rings signal connect to Trinket Pin #0
#define NUMPIXELS 32 // 16 LEDs per ring, 32 for two rings

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN); 

uint8_t  mode   = 0, // Current animation effect <2>
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

void setup() {    // <3>
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
  prevTime = millis();
}

void loop() {   // <4>
  uint8_t  i;
  uint32_t t;

  switch(mode) {  // <5>

    case 0: // Random sparks - just one LED on at a time!
      i = random(NUMPIXELS);
      pixels.setPixelColor(i, color);
      pixels.show();
      delay(10);
      pixels.setPixelColor(i, 0);
      break;
    case 1: // Spinny wheels (8 LEDs on at a time)
      for(i=0; i<16; i++) {
        uint32_t c = 0;
        if(((offset + i) & 7) < 2) c = color; // 4 pixels on...
        pixels.setPixelColor(   i, c); // First eye
        pixels.setPixelColor(31-i, c); // Second eye (flipped)
      }
    pixels.show();
    offset++;
    delay(50);
    break;
  }
  t = millis();
  if((t - prevTime) > 8000) { // Every 8 seconds... <6>
    mode++; // Next mode
    if(mode > 1) { // End of modes?
      mode = 0; // Start modes over
      color >>= 8; // Next color R->G->B
      if(!color) color = 0xFF0000; // Reset to red
    }
  for(i=0; i<NUMPIXELS; i++) pixels.setPixelColor(i, 0); // <7>
     prevTime = t;
  }
}
/*
<1> We must include the Adafruit Neopixel library which is obtained from https://github.com/adafruit/Adafruit_NeoPixel and installed per instructions in Chapter 1.
<2> Initialize the variables +mode+ and +color+ for lighting effects.
<3> Setup initializes the data the Neopixel rings in +strip+.  The brightness is set also, you can vary the brightness from off (0) to full (255).  Battery life is saved if you keep the brightness down (and Neopixel LEDS are very bright at 255).
<4> If fifferent animations are desired, change the code in the +loop+ function.
<5> Two modes are preprogrammed - sparks (single pixels) and spinny wheels (8 LEDs at one time).
<6> Currently the animation mode is changed every 8 seconds.  On every mode change, the color is shifted through red, green, and blue.
<7> This final loop sets the colors on the rings before looping back.
*/
