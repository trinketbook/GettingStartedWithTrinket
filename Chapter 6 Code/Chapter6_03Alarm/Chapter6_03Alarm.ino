/* Trinket Alarm System 

   From Chapter 6 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Initial Version
*/
#define SerialPin 0 // Serial via Bluefruit EZ-Link on this pin
#define LEDpin 1    // Use Trinket LED for displaying tripped sensors
#define SensorPin 3 // A3 which is Pin #3 has resistor network to read
                    //   3 normally closed sensors
//#define DEBUG     // <1>
#include <SoftwareSerial.h> // Software serial library <2>

SoftwareSerial Serial(2,0);   // <3>
const uint8_t numSensors = 3; // number of sensors <4>
const uint8_t states = 8;     // 2^numsensors
uint16_t values[8] = {541, 685, 661, 614, 840, 780, 776, 997};
char *textval[8] = {"Set","PIR", "2", "3","PIR+2","PIR+3","2+3","All"}; // <5>

void setup() {
  pinMode(LEDpin, OUTPUT);   // Set Pin #1 to output for LED blinking
  pinMode(SensorPin, INPUT); // sets analog pin for input
  Serial.begin(9600);        // Send status information via serial
  Serial.println("Alarm System"); // <6>
}

void loop()  {
  int8_t contact;         // read alarm loops (returns -1 if a read error)
  
  contact = readContact(SensorPin); // <7>
  if(contact >= 1) {         // if any value greater than 0(set),
    Blink(LEDpin, contact);  // we have an alarm! Blink LED corresponding to
    Serial.print("Alarm! "); // which sensor(s) and write to Bluetooth
    Serial.println(textval[contact]);
  }
  else if(contact < 0) {    // a bad analog read was done. If you get errors
    Serial.print("Error");  // set DEBUG, walk test, record values, and
  }                         // update code with analogread values
  else {
    Serial.println("Set");  // Alarm is set (no sensors tripped), alls well
  }

 delay(500); // We do not need to poll the sensors often (changeable)
}

int8_t readContact(uint8_t TrinketPin) {  // <8>
// returns the number corresponding to sensor values.
// TrinketPin is the analog pin on the Trinket (A1=#2, A2=#4, A3=#3)

  const int variance = 8; // Analog readings can vary, value for +-variance
  int contact = 0;
  uint16_t readval = 0;
  readval = analogRead(TrinketPin); // Check the pin

#ifdef DEBUG
 Serial.print(": Sensor read value: ");
 Serial.println(readval);
#endif

  for(uint8_t i=0; i<states; i++) { // if reading is near state value,
                                    //   return that state
    if(readval >= (values[i]-variance) && readval <= (values[i]+variance) )    
      {
      return(i);
      }
  }
  return -1; // value not one of the alarm system values
}

void Blink(uint8_t pin, uint8_t times) {  // <9>
  for(uint8_t i=1; i<=times; i++) {
    digitalWrite(pin, HIGH);
    delay(85);
    digitalWrite(pin, LOW);
    delay(85);
  }
}
/*
<1> If this line is uncommented, the debug code will be included
<2> Serial connects the Bluefruit EZ-Link RX pin connected to Pin #0 of Trinket. A terminal program 
(such as freeware PuTTY for Windows) is used to get the alerts.  A Processing or Python script looking 
for alarms could be used to automate monitoring
<3> Serial transmission on Trinket Pin #0, receive Pin #2 (not used here).  SendOnlySoftwareSerial may 
also be used for the transmission without receive.  If Pin #2 is used for a sensor branch, this should 
be changed.
<4> Multiplex 3 normally closed sensors on one analog pin. If you have 2 sensors, you can leave the 
one resistor open and adjust the text values.
<5> Text values are mapped to all the different states of sensor open and close to alert the monitor.  
This can also be done at the receive end if a number is passed instead of text.
<6> The receiver can look for this text to determine the alarm was turned on or restarted.
<7> If the alarm sensor configuration is changed (more sensors, etc.), change the readContacts function.
<8> readContacts should return 0 for no alarm, -1 for errors, and a number to indicate which alarms 
are going off.  The logic can be changed here to add more sensors.
<9> This routine toggles a pin the number of times requested. Good to use on an LED pin to output 
which sensors are triggered.
*/
