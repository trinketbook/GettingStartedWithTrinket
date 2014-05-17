/* LED "Color Organ" for Adafruit Trinket and Neopixel LEDs

   From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/

#include <Adafruit_NeoPixel.h>  

#define N_PIXELS   19  // Number of pixels you are using // <1>
#define MIC_PIN     1  // Microphone is attached to Trinket Pin #2/(A1) <2>
#define LED_PIN     0  // NeoPixel LED strand is connected to Pin #0 <3>
#define DC_OFFSET   0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     100  // Noise/hum/interference in mic signal
#define SAMPLES    60  // Length of buffer for dynamic level adjustment
#define TOP   (N_PIXELS +1) // Allow dot to go slightly off scale

// Comment out the next line if you do not want brightness control
#define POT_PIN    3  // if defined, a potentiometer is on Pin #3 (A3) <4>

byte
  peak     = 0,    // Used for falling dot
  dotCount = 0,    // Frame counter for delaying dot-falling speed
  volCount = 0;    // Frame counter for storing past volume data

int
  vol[SAMPLES],       // Collection of prior volume samples
  lvl       = 10,     // Current "dampened" audio level
  minLvlAvg = 0,      // For dynamic adjustment of graph low & high
  maxLvlAvg = 512;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  memset(vol, 0, sizeof(vol));  // Clear the sample array
  strip.begin();
}

void loop() {
  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int      n, height;

  n   = analogRead(MIC_PIN);         // Raw reading from mic <5>
  n   = abs(n - 512 - DC_OFFSET);            // Center on zero
  n   = (n <= NOISE) ? 0 : (n - NOISE);      // Remove noise/hum
  lvl = ((lvl * 7) + n) >> 3;    // Dampened reading (else looks twitchy)

  // Calculate bar height based on dynamic min/max levels (fixed point)
  height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);
  if(height < 0L)       height = 0;      // Clip output
  else if(height > TOP) height = TOP;
  if(height > peak)     peak   = height; // Keep 'peak' dot at top

// if POT_PIN is defined, we have a potentiometer on Pin #3 on Trinket
  uint8_t bright = 255;

#ifdef POT_PIN
bright = analogRead(POT_PIN); // <6>
#endif
  strip.setBrightness(bright); 
  
  for(i=0; i<N_PIXELS; i++) {  // <7>
    if(i >= height)
      strip.setPixelColor(i, 0, 0, 0);
    else
      strip.setPixelColor(i,Wheel(map(i,0,strip.numPixels()-1,30,150)));
  }
  strip.show(); // Update strip
 
  vol[volCount] = n;                      // Save for dynamic leveling
  if(++volCount >= SAMPLES) volCount = 0; // Rollover sample counter
 
  // Get volume range of prior frames <8>
  minLvl = maxLvl = vol[0];
  for(i=1; i<SAMPLES; i++) {
    if(vol[i] < minLvl)      minLvl = vol[i];
    else if(vol[i] > maxLvl) maxLvl = vol[i];
  }
  if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
  minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
  maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)
}

uint32_t Wheel(byte WheelPos) { // <9>
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
      WheelPos -= 85;
      return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
/*
<1> Change this value if your build has a different number of Neopixels
<2> If you change the pin for the microphone, change this value.  Use the analog pin number, not the Trinket (digital) pin number per Chapter 1.
<3> The Neopixel pin can be changed to any digital pin.
<4> A potentiometer to adjust the pixels is recommended.  Ensure the analog pin the potentiometer center lug is defined.  Picking Analog 3 (Trinket Pin #3), you must remove Trinket to program it (PPins #3 and #4 are shared with the USB port).
<5> The value from the microphone is read here.  It is then conditioned such that low volumes tend to turn pixels off, loud continuous volumes of sound make most the pixels light.
<6> If a potentiometer is connected, read it and use the value to set the brightness of the LEDs
<7> Color pixels based on rainbow gradient.  If you want other color schemes, you can change the pixel color setting algorithm here.
<8> minLvl and maxLvl indicate the volume range over prior frames, used for vertically scaling the output graph (so it looks interesting regardless of volume level). If they're too close together though (e.g. at very low volume levels) the graph becomes super coarse
and 'jumpy'...so some minimum distance is kept between them (this also lets the graph go to zero when no sound is playing).
<9> An input value of 0 to 255 returns a color value that transitions from r - g - b - back to r.
*/
