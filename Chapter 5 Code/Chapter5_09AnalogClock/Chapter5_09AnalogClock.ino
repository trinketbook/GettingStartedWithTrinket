/* Trinket analog meter clock  

  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
*/

#include <TinyWireM.h>
#include <TinyRTClib.h>  // <1>
//#include <SendOnlySoftwareSerial.h> 

#define HOUR_PIN   1 // Hour   display via PWM on Trinket Pin #1
#define MINUTE_PIN 4 // Minute display via PWM on Trinket Pin #4

RTC_DS1307 rtc;   // <3>
//SendOnlySoftwareSerial Serial(3);  // <2>

void setup () {
  pinMode(HOUR_PIN, OUTPUT);  // <4>
  pinMode(MINUTE_PIN, OUTPUT);
  PWM4_init();   // <5>
 
  TinyWireM.begin();       // Begin I2C
  rtc.begin();             // Begin DS1307 real time clock
  //Serial.begin(9600);    // Begin Serial Monitor at 9600 baud
  if (! rtc.isrunning()) {
    //Serial.println("RTC is NOT running!");  // <6>
    //rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop () {
  uint8_t hourvalue, minutevalue;
  uint8_t hourvoltage, minutevoltage;
 
  DateTime now = rtc.now(); // <7>
  hourvalue = now.hour();  
  if(hourvalue > 12) hourvalue -= 12; // This clock is 12 hour, is 13-24, 
                                      //  convert to 1-12
  minutevalue = now.minute();         

  hourvoltage = map(hourvalue, 0, 12, 0, 255);  // <8>
  minutevoltage = map(minutevalue, 0, 60, 0, 255);  

/* Uncomment out this and other serial code to check that clock is working
  Serial.print(now.year(), DEC);    Serial.print('/');
  Serial.print(now.month(), DEC);   Serial.print('/');
  Serial.print(now.day(), DEC);     Serial.print(' ');
  Serial.print(now.hour(), DEC);    Serial.print(':');
  Serial.print(now.minute(), DEC);  Serial.print(':');
  Serial.print(now.second(), DEC);  Serial.print(" - ");
  Serial.print(hourvoltage, DEC);   Serial.print(' ');
  Serial.print(minutevoltage, DEC); Serial.println();
*/
  analogWrite(HOUR_PIN, hourvoltage); // <9>
  analogWrite4(minutevoltage);

  delay(5000); // check time every 5 seconds. You can change this.
}

void PWM4_init() {  // <10>
  TCCR1 = _BV (CS10);                  // no prescaler
  GTCCR = _BV (COM1B1) | _BV (PWM1B);  // clear OC1B on compare
  OCR1B = 127;                  // duty cycle initialize to 50%
  OCR1C = 255;                  // frequency
}

void analogWrite4(uint8_t duty_value) {  // <11>
  OCR1B = duty_value; // duty may be 0 to 255 (0 to 100%)
}
/*
<1> The TinyRTClib is an integer version of the Adafruit RTClib Arduino library
<2> For debugging, uncomment the serial code.  Use an FTDI Friend with its RX pin connected to Trinket Pin #3. You will need a terminal program (such as freeware PuTTY for Windows) set to the USB port of the FTDI friend at 9600 baud. 
<3> Set up the real time clock data structure
<4> Define the two meter pins as outputs (must be pulse-width modulation capable pins)
<5> Set timer 1 to output PWM on Trinket Pin #4
<6> This code should be run once then the lines commented out and the code reloaded.  This sets the clock with the date and time on the programming computer when the sketch was compiled
<7> Get the real-time clock info (hour and minute)
<8> Convert hours and minutes into pulse-width duty cucle for meter display.  f you have calibration issues, you can change the last two values (zero higher, 255 lower) to have the needle move less if your scale is not pasted on 100% straight.
<9> The pulse width to the meters is set here which is proportional to the time.
<10> Custom function to initialize PWM on Trinket Pin #4
<11> Function analogous to analogWrite which works on Trinket Pin #4
*/
