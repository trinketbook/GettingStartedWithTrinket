/* Trinket Rover 

   From Chapter 6 of Getting Started with Trinket by Mike Barela, 2014  
   Version 1.0 - Rick Winscot
*/
#include <Adafruit_SoftServo.h>

#define SERVO1PIN 0 // Servo control line (orange) on Trinket Pin #0
#define SERVO2PIN 1 // Servo control line (orange) on Trinket Pin #1
Adafruit_SoftServo servo_left, servo_rght;

const int sonar = 2;       // Sensor on Trinket Pin #2
const int left_speed = 75; // <1>
const int rght_speed = 90;
const int obstacle = 8;     // <2>
const int back_track = 100; // <3>
long duration, inches, cm;

void setup() {
  servo_left.attach(SERVO1PIN); // Attach servos... 
  servo_rght.attach(SERVO2PIN); //   and off we go!
}

void loop() {
  servo_left.write(left_speed - cm); // Setting servos 
  servo_left.refresh();              //  in forward motion
  servo_rght.write(rght_speed + cm);
  servo_rght.refresh();
  delay(15);
  duration = 0;  // <4>
  inches   = 0;
  cm       = 0;
  pinMode(sonar, OUTPUT);  // <5>
  digitalWrite(sonar, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonar, LOW);
  pinMode(sonar, INPUT); // <6>
  duration = pulseIn(sonar, HIGH);
  inches = microsecondsToInches(duration); // convert time into distance.
  cm = microsecondsToCentimeters(duration);
  if ( cm < obstacle ) {  // <7>
    for (int i = 0; i < back_track; i++) { // <8>
      servo_left.write(150);
      servo_left.refresh();
      servo_rght.write(50);
      servo_rght.refresh();
      delay(15);
    }
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2; // <9>
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2; // <10>
}
/*
<1> Moderate speed forward for both servos. Given the servos orientation one will be going forward, 
and the other backward. You may need to adjust these slightly to get the rover to move straight forward.
<2> Number in centimeters the rover will reverse and try to navigate around.
<3> Multiplier used to determine how far the rover will back-up.
<4> Establish variables for duration of the ping, and the distance result in inches & centimeters.
<5> The PING is triggered by a HIGH pulse of 2 or more microseconds. Give a short LOW pulse beforehand
to ensure a clean HIGH pulse.
<6> The sonar pin is used to read the signal from the PING: a HIGH pulse whose duration is the 
time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
<7> back_track * delay(15) = distance the rover will back-up during obstacle avoidance.
<8> These are magic numbers, the rover will always backup the same direction. Is there a better
way to navigate obstacles?
<9> According to Parallax's datasheet for the PING, there are 73.746 microseconds per inch
(i.e. sound travels at 1130 feet per second). This gives the distance traveled by the ping, 
outbound and return, so divide by 2 to get the distance of the obstacle. See 
http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
<10> The speed of sound is 340 m/s or 29 microseconds per centimeter. The ping travels out 
and back, so to find the distance of the object, half of the distance traveled is taken.
*/
