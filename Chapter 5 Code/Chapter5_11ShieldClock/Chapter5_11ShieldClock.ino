/* Trinket RGB LCD Shield Clock
   The DS1307 Real Time Clock must be initialized with a separate sketch.

   From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/
#include <TinyWireM.h>                 // Trinket I2C communications
#include <TinyAdafruit_RGBLCDShield.h> // RGB LCD Shield communications
#include <TinyRTClib.h>                // DS1307 clock communications

#define OFF    0x0  // <1>
#define RED    0x1
#define YELLOW 0x3
#define GREEN  0x2
#define TEAL   0x6
#define BLUE   0x4
#define VIOLET 0x5
#define WHITE  0x7

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield(); // <2>
RTC_DS1307 RTC; 

DateTime Clock;    // Holds current clock time
int8_t offset = 0; // Hour offset set by user with buttons
uint8_t backlight = WHITE; // Backlight state

void setup() {
  RTC.begin();             // Initialize clock
  lcd.begin(16, 2);        // initialize display columns and rows
  lcd.setBacklight(WHITE); // <3>
}

void loop() {
  uint8_t buttons;         // button read value
  uint8_t hourval, minuteval, secondval; // holds the time
 
  DateTime Clock;          // variable to hold our time
  char* colon = ":"; // <4>
  char* slash = "/";    
  Clock = RTC.now(); // <5>
  hourval = Clock.hour()+offset;  // <6>   
  if(hourval > 23) hourval-=24;     
  else if(hourval < 0) hourval+=24;  
  minuteval = Clock.minute();        
  secondval = Clock.second();  
  lcd.setCursor(0,0);           // <7>
  if(hourval < 10) printzero(); 
  lcd.print(hourval);               
  lcd.print(colon);
  if(minuteval < 10) printzero();
  lcd.print(minuteval);
  lcd.print(colon);
  if(secondval < 10) printzero();
  lcd.print(secondval);
 
  buttons = lcd.readButtons(); // <8>
  if(buttons!=0) { 
    if (buttons & BUTTON_UP) { // if up pressed, increment hours
      offset +=1;
    }
    if (buttons & BUTTON_DOWN) { // if down pressed, decrement hours
      offset -=1;
    }
    if (buttons & BUTTON_SELECT) { // if select button pressed
      if(backlight)                // if the backlight is on
        backlight=OFF;             // set it to off
      else                // else turn on the backlight if off
        backlight=WHITE;          //  (you can select any color)
      lcd.setBacklight(backlight); // set the new backlight state
    }
  }

  lcd.setCursor(0,1); // <9>
  if(Clock.month()<10) printzero();  
  lcd.print(Clock.month());
  lcd.print(slash);
  if(Clock.day()<10) printzero();
  lcd.print(Clock.day());
  lcd.print(slash);
  lcd.print(Clock.year());
  delay(1000); // wait one second
}

void printzero() { // prints a zero to the LCD for leading zeros
  lcd.print("0");  // a function saves multiple print function calls
}
/*
<1> The values here make it easy to set the backlight color
<2> The shield uses the I^2^C SCL and SDA lines, Trinket Pins #0 and #2.  Also set the clock data object.
<3> Set the LCD backlight color here.  Use OFF to not set the backlight.
<4> Static values, which can be reused, saves a tiny bit of memory.
<5> Get the time from the real-time clock
<6> Adjust the hour based on a daylight savings hour in variable offset.
<7> Print date and time to LCD (with leading zeros for single digit values.
<8> If the buttons are pressed, act on them (up and down for daylight savings, select to toggle the backlight).
<9> Print the date to the LCD
*/
