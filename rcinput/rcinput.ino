#include <Servo.h>

byte rightStop = 92;
byte rightForward = 0;
byte rightReverse = 255;
byte leftStop = 92;
byte leftForward = 255;
byte leftReverse = 0;
Servo leftWheel;
Servo rightWheel;
 
int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;

void setup() {

  leftWheel.attach(10);
  rightWheel.attach(9);
  pinMode(5, INPUT); // Set our input pins as such
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600); // Pour a bowl of Serial
  leftWheel.write(leftStop);
  rightWheel.write(rightStop);
}

void loop() {

  
  ch1 = pulseIn(5, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(6, HIGH, 25000); // each channel
  //ch3 = pulseIn(7, HIGH, 25000);

  Serial.print("Channel 1:"); // Print the value of 
  Serial.println(ch1);        // each channel

  Serial.print("Channel 2:");
  Serial.println(ch2);

  //Serial.print("Channel 3:");
  //Serial.println(ch3);
  if ((ch1 == 0) && (ch2 == 0)) {
    stopRobot();
  }
  if (ch1 > 1425) {
    leftWheel.write(leftForward);
    rightWheel.write(rightForward);
  }
  else if ((ch1 < 1380) && (ch1 != 0)) {
    leftWheel.write(leftReverse);
    rightWheel.write(rightReverse);
  }
  else if (ch2 > 1515) {
    leftWheel.write(leftForward);
    rightWheel.write(rightReverse);
  }
  else if (ch2 < 1480) {
    leftWheel.write(leftReverse);
    rightWheel.write(rightForward);
  }
  else{
    if ((ch1 == 0) && (ch2 == 0)) {
      stopRobot();
    }
    stopRobot();
  }
  delay(500); // I put this here just to make the terminal 
              // window happier
}

void stopRobot() {
  leftWheel.write(leftStop);
  rightWheel.write(rightStop);
}
