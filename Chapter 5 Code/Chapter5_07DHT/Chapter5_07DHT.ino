/* Trinket I2C Display and DHT Sensor Sketch 

  From Chapter 5 of Getting Started with Trinket by Mike Barela, 2014  
  Version 1.0 - Initial Version
*/

#include <TinyWireM.h>         // Wire/I2C library for Trinket <1> 
#include <TinyLiquidCrystal.h> // LiquidCrystal using TinyWireM
#include <TinyDHT.h>           // lightweight DHT sensor library
#include <avr/power.h>   // needed to up clock to 16 MHz on 5v Trinket

#define DHTTYPE DHT22   // DHT 22 (AM2302) <2>
#define TEMPTYPE 1      // <3>
#define DHTPIN 1        // The sensor is connected to Pin #1 

DHT dht(DHTPIN, DHTTYPE); // <4>
TinyLiquidCrystal lcd(0); // <5>

void setup() { 
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1); // <6>
  dht.begin();            // Start temperature sensor
  lcd.begin(16, 2);       // <7>
  lcd.setBacklight(HIGH); 
}

void loop() {
  int8_t h = dht.readHumidity();             // <8>
  int16_t t = dht.readTemperature(TEMPTYPE); 

  lcd.setCursor(0, 0);
  if ( t == BAD_TEMP || h == BAD_HUM ) { // <9>
    lcd.print("Bad read on DHT");        // <10>
  } else {
    lcd.print("Humidity: "); // write values to LCD
    lcd.setCursor(10, 0);  lcd.print(h);
    lcd.setCursor(12, 0);  lcd.print(" % ");
    lcd.setCursor( 0, 1);  lcd.print("Temp:");
    lcd.setCursor( 7, 1);  lcd.print(t);
    lcd.setCursor(10, 1);  lcd.print("*F");
  }
  delay(2000); // Read values every 2 seconds (2000 milliseconds) <11>
}
/*
<1> Load the libraries needed for the program.
<2> The sensor type can be defined as DHT11, DHT21 or DHT22.
<3> Define thus variable for temperature scale: 1 for Fahrenheit, 0 for Celsius
<4> Initialize temperature sensor data structure.
<5> Initialize display connected via I2C, default address 0 (backpack A0-A2 not jumpered)
<6> This special line sets the Trinket to run at 16 MHz.
<7> The display is defined as 2 rows, 16 columns and the backlight is turned on
<8> Read the humidity, then the temperature (note data sizes are different)
<9> File TinyDHT.h defines the values for the variables when the sensor is reading funky values.
<10> If an error value is returned, display it on the LCD, otherwise print the humidity and temperature on the display.
<11> The sensor does not like reads faster than once every two seconds per the datasheet.
*/
