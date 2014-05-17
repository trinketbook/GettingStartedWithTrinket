/*
   Sketch to set the time and date for the DS1307 Real Time Clock
   with an Adafruit Trinket mini microcontroller
 
   From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/

#include <TinyWireM.h>
#include <TinyRTClib.h>

RTC_DS1307 RTC;

void setup() {
  RTC.begin();
  if(!RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {}  // Nothing to do in loop, clock set in setup