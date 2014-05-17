/* Trinket Ultrasonic Rangefinder Sketch 

  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
*/
#include <TinyWireM.h>         // <1>
#include <TinyLiquidCrystal.h> 
#define  EZ1pin 1              // <2>

TinyLiquidCrystal lcd(0);  // <3>

int8_t arraysize = 9; // <4>
uint16_t rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t modE;        // calculated mode (most common) distance

void setup() {
  pinMode(EZ1pin, INPUT); // Set ultrasonic sensor pin as input
  lcd.begin(16, 2);       // <5>
  lcd.setBacklight(HIGH); 
}

void loop() {
  int16_t pulse;   // number of pulses from sensor
  int i=0;

  while( i < arraysize )
    { pulse = pulseIn(EZ1pin, HIGH); // read in time for pin to transition
      rangevalue[i]=pulse/58;        // pulses to centimeters
                                     // (use 147 for inches)
      if( rangevalue[i] >= 15 && rangevalue[i] < 645 ) i++; // <6>
      delay(10);                     // wait between samples
    }
  isort(rangevalue,arraysize);       // sort samples
  modE = mode(rangevalue,arraysize); // get median, the value desired

  lcd.setCursor( 0,0); lcd.print("Range: ");  // <7>
  lcd.setCursor( 7,0); lcd.print("    ");
  lcd.setCursor( 7,0); lcd.print(modE);
  lcd.setCursor(11,0); lcd.print("cm");

  delay(500); // Read every half second
}

void isort(uint16_t *a, int8_t n) {  // <8>
  for (int i = 1; i < n; ++i) {
    uint16_t j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)  {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

uint16_t mode(uint16_t *x,int n) {  // <9>
  int i = 0;
  int count = 0;
  int maxCount = 0;
  uint16_t mode = 0;
  int bimodal;
  int prevCount = 0;

  while(i<(n-1)) {
    prevCount=count;
    count=0;
    while( x[i]==x[i+1] ) {
      count++;
      i++;
    }
    if( count > prevCount & count > maxCount) {
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if( count == 0 ) {
      i++;
    }
    if( count == maxCount ) { //If the dataset has 2 or more modes.
      bimodal=1;
    }
    if( mode==0 || bimodal==1 ) { // Return median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}
/*
<1> Include the libraries needed (the Maxbotix does not need a library).
<2> The sensor is on Trinket Pin #1
<3> The display is on the I^2^C pins, address 0 (A0-A2 not jumpered)
<4> Define the number of values to calculate the median (sample size, needs to be an odd number).
<5> Set up the LCD: number of rows and columns, set the backlight on 
<6> Ensure the value read is in range, if so, save the value
<7> Write the distance to the LCD display via the attached I^2^C backpack
<8> Sorting function - portions of code provided for free use on http://playground.arduino.cc/Main/MaxSonar by Bruce Allen and Bill Gentles
<9> Mode function, returning the mode (most common value) or median if no one mode.
*/
