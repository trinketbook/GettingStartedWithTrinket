/* Getting Started with Trinket - Two Neopixel Program 

From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
Version 1.0 - Initial Version
*/
#include <Adafruit_NeoPixel.h> // Add in the Adafruit Neopixel library <1>

#define PIN       0 // Neopixel signal output pin <2>
#define NUMPIXELS 2 // How many pixels we will use

// Set the Neopixel data structures and operation
Adafruit_NeoPixel strip = 
  Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() { // <3>
  strip.begin(); // This sets up Neopixels for use
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  int8_t i; // <4>

  for(i=0; i <= 255; i++) { // <5>
    // Cycle the first Neopixel up in Blue, the second down in red
    strip.setPixelColor(0,strip.Color(    0,0,i)); // <6>
    strip.setPixelColor(1,strip.Color(255-i,0,0)); 
    strip.show();
    delay(6);
  }

  delay(100);

  for(i=255; i >=0 ; i--) { 
    // Cycle the first Neopixel down in blue, the second up in red
    strip.setPixelColor(0,strip.Color(    0,0,i));
    strip.setPixelColor(1,strip.Color(255-i,0,0));
    strip.show();
    delay(6);
  }

  delay(100);
}
/*
<1> We must include the Adafruit Neopixel library which you can obtain from https://github.com/adafruit/Adafruit_NeoPixel and install per instructions in <<chap-libraries>>.
<2> We make some definitions allowing us to easily change things: the pin on Trinket to connect to the Neopixels and how many pixels we will drive. The last values--+NEO_GRB+ and +NEO_KHZ800+ are the values for all the Neopixels now sold by Adafruit (other values can be used with some other brands of smart LEDs). 
<3> Setup initializes the data structure our definition of 'strip' set. 
The loop cycles the color of the LEDs, the first one cycles up then down in blue, the red cycles down then up in red. 
<4> Variable +i+ is an 8 bit unsigned integer +uint8_t+ which should be fine as long as we restrict its use to between 0 and 255 per <<chap-libraries>>.
<5> Each time through the loop function, we directly manipulate the blue value (the third parameter in the +Color+ function) and the red value (the first parameter). The green value (the second value) is left at zero. If you like green over red, you can change it to a fixed number or cycle it as a function of variable +i+ or +255-i+. 
<6> The +strip.Color+ function takes three numbers, a red, green, and blue value from 0 to 255 (low/off to high/full on).  The return value is a single 32 bit (long) number for the combined color.  The +strip.setPixelColor+ call takes two values: the pixel number and the 32 bit color number. This is why we have +strip.Color+ nested into the +setPixelColor+ function call. 
*/