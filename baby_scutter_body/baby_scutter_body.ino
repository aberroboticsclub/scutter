#include <NewPing.h>

//Debug lines off FALSE
//Debug lines on TRUE
#define DEBUG_MAPRC false
#define DEBUG_ACTRC false


//The time for the serial print delay
#define printDelay 500


//Motor Pins
int leftMotor = 10;
int rightMotor = 11;

//Motor Values
const int stopValue = 128;
int potForward;
int potReverse;

const int reverseMax = 90;
const int forwardMax = 166;


//RC variables
const int ch1Pin = 2;
const int ch2Pin = 3;
const int ch3Pin = 4;
const int ch4Pin = 5;
const int ch5Pin = 6;
const int ch6Pin = 7;

int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;

int ch1Mapped;
int ch1MappedR;
int ch2Mapped;
int ch3Mapped;
int ch4Mapped;
int speedPotForward;
int speedPotReverse;
int ch6Mapped;
bool rcKill = false;


void setup() {
  Serial.begin(9600);
  pinMode(flickSwitchPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch4Pin, INPUT);
  pinMode(ch5Pin, INPUT);
  pinMode(ch6Pin, INPUT);

  analogWrite(leftMotor, stopValue);
  analogWrite(rightMotor, stopValue);

  delay(2000);
  digitalWrite(relay, HIGH);
}


void loop() {
  RC();
}


void RC() {
  //Serial.println("This function will convert all the remote control values");
  //delay(printDelay);
  mapRC();
  actRC();
}



void actRC() {
  if ((ch2Mapped > 130) && ((ch1Mapped > 125) && (ch1Mapped < 130))) { //forward
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Forwards |  ");
      Serial.print("left motor ");
      Serial.print(ch2Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch2Mapped);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch2Mapped);
    analogWrite(rightMotor, ch2Mapped);
  }

  if ((ch2Mapped > 130) && (ch1MappedR > 130)) { //forward swing left
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Forwards and Swing Left |  ");
      Serial.print("left motor ");
      Serial.print(ch2Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch1MappedR);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch2Mapped);
    analogWrite(rightMotor, ch1MappedR);
  }

  if ((ch2Mapped > 130) && (ch1Mapped > 130)) { //forward swing right
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Forwards and Swing Right |  ");
      Serial.print("left motor ");
      Serial.print(ch1Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch2Mapped);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch1Mapped);
    analogWrite(rightMotor, ch2Mapped);
  }


  if ((ch2Mapped < 125) && ((ch1Mapped > 125) && (ch1Mapped < 130))) { //reverse
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Reverse |  ");
      Serial.print("left motor ");
      Serial.print(ch2Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch2Mapped);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch2Mapped);
    analogWrite(rightMotor, ch2Mapped);
  }

  if ((ch2Mapped < 125) && (ch1MappedR < 125)) { //reverse and swing right
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Reverse and Swing Right |  ");
      Serial.print("left motor ");
      Serial.print(ch1MappedR);
      Serial.print(" | right motor ");
      Serial.println(ch2Mapped);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch1MappedR);
    analogWrite(rightMotor, ch2Mapped);
  }

  if ((ch2Mapped < 125) && (ch1Mapped < 125)) { //reverse and swing left
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Reverse and Swing Left |  ");
      Serial.print("left motor ");
      Serial.print(ch2Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch1Mapped);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch2Mapped);
    analogWrite(rightMotor, ch1Mapped);
  }


  if (((ch2Mapped > 125) && (ch2Mapped < 130) && (ch1Mapped < 125) && (ch1MappedR > 130))) { //spin left
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Spin Left |  ");
      Serial.print("left motor ");
      Serial.print(ch1Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch1MappedR);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch1Mapped);
    analogWrite(rightMotor, ch1MappedR);
  }


  if (((ch2Mapped > 125) && (ch2Mapped < 130) && (ch1Mapped > 130) && (ch1MappedR < 125))) { //spin right
#ifdef DEBUG_ACTRC
    if (DEBUG_ACTRC == true) {
      Serial.print("Spin Right |  ");
      Serial.print("left motor ");
      Serial.print(ch1Mapped);
      Serial.print(" | right motor ");
      Serial.println(ch1MappedR);
      delay(printDelay);
    }
#endif
    analogWrite(leftMotor, ch1Mapped);
    analogWrite(rightMotor, ch1MappedR);
  }


  if (((ch2Mapped > 125) && (ch2Mapped < 130)) && ((ch1Mapped > 125) && (ch1Mapped < 130))) {
    rcStop();
  }
}


void mapRC() {
  ch5 = pulseIn (ch5Pin, HIGH);
  if (ch5 != 0) {
    speedPotForward = map(ch5, 995, 2008, 5, 250);
    speedPotReverse = map(ch5, 995, 2008, 250, 5);
  }
#ifdef DEBUG_MAPRC
  if (DEBUG_MAPRC == true) {
    Serial.print("Channel 5: Source: ");
    Serial.println(ch5);
    Serial.print("Channel 5: Mapped: ");
    Serial.println(speedPotForward);
    Serial.print("Channel 5: MappedR: ");
    Serial.println(speedPotReverse);
    delay(printDelay);
  }
#endif


  ch1 = pulseIn (ch1Pin, HIGH);
  if (ch1 != 0) {
    ch1Mapped = map(ch1, 1310, 1690, speedPotReverse, speedPotForward);
    ch1MappedR = map(ch1, 1310, 1690, speedPotForward, speedPotReverse);
  }
#ifdef DEBUG_MAPRC
  if (DEBUG_MAPRC == true) {
    Serial.print("Channel 1: Source: ");
    Serial.println(ch1);
    Serial.print("Channel 1: Mapped: ");
    Serial.println(ch1Mapped);
    Serial.print("Channel 1: MappedR: ");
    Serial.println(ch1MappedR);
    delay(printDelay);
  }
#endif


  ch2 = pulseIn (ch2Pin, HIGH);
  if (ch2 != 0) {
    ch2Mapped = map(ch2, 1320, 1660, speedPotReverse, speedPotForward);
  }
#ifdef DEBUG_MAPRC
  if (DEBUG_MAPRC == true) {
    Serial.print("Channel 2: Source: ");
    Serial.println(ch2);
    Serial.print("Channel 2: Mapped: ");
    Serial.println(ch2Mapped);
    delay(printDelay);
  }
#endif


  ch3 = pulseIn (ch3Pin, HIGH);
  if (ch3 != 0) {
    ch3Mapped = map(ch3, 1150, 1820, speedPotReverse, speedPotForward);
  }
#ifdef DEBUG_MAPRC
  if (DEBUG_MAPRC == true) {
    Serial.print("Channel 3: Source: ");
    Serial.println(ch3);
    Serial.print("Channel 3: Mapped: ");
    Serial.println(ch3Mapped);
    delay(printDelay);
  }
#endif


  ch4 = pulseIn (ch4Pin, HIGH);
  if (ch4 != 0) {
    ch4Mapped = map(ch4, 1310, 1685, speedPotReverse, speedPotForward);
  }
#ifdef DEBUG_MAPRC
  if (DEBUG_MAPRC == true) {
    Serial.print("Channel 4: Source: ");
    Serial.println(ch4);
    Serial.print("Channel 4: Mapped: ");
    Serial.println(ch4Mapped);
    delay(printDelay);
  }
#endif
}


void rcForwards() {
  analogWrite(leftMotor, 166);
  analogWrite(rightMotor, 166);
}


void rcReverse() {
  analogWrite(leftMotor, 90);
  analogWrite(rightMotor, 90);
}


void rcLeft() {
  analogWrite(leftMotor, 90);
  analogWrite(rightMotor, 166);
}


void rcRight() {
  analogWrite(leftMotor, 166);
  analogWrite(rightMotor, 90);
}


void rcStop() {
  analogWrite(leftMotor, stopValue);
  analogWrite(rightMotor, stopValue);
}


void pingSonar() {
  sonarValue1 = sonar1.ping_cm();
  sonarValue2 = sonar2.ping_cm();
  sonarValue3 = sonar3.ping_cm();
  sonarValue4 = sonar4.ping_cm();
  sonarValue5 = sonar5.ping_cm();
  sonarValue6 = sonar6.ping_cm();

#ifdef DEBUG_SONAR
  if (DEBUG_SONAR == true) {
    printSpacer();
    Serial.print("Sonar 1 is ");
    Serial.print(sonarValue1);
    Serial.println(" cm");
    Serial.print("Sonar 2 is ");
    Serial.print(sonarValue2);
    Serial.println(" cm");
    Serial.print("Sonar 3 is ");
    Serial.print(sonarValue3);
    Serial.println(" cm");
    Serial.print("Sonar 4 is ");
    Serial.print(sonarValue4);
    Serial.println(" cm");
    Serial.print("Sonar 5 is ");
    Serial.print(sonarValue5);
    Serial.println(" cm");
    Serial.print("Sonar 6 is ");
    Serial.print(sonarValue6);
    Serial.println(" cm");
    delay(printDelay);
  }
#endif
}


void printSpacer() {
  Serial.println("---------------------------------------");
}
