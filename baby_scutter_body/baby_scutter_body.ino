#include <NewPing.h>

//Debug lines off FALSE
//Debug lines on TRUE
#define DEBUG_SONAR false
#define DEBUG_FLICKSWITCH false
#define DEBUG_MAPRC false
#define DEBUG_ACTRC false


//The time for the serial print delay
#define printDelay 500


//Define Sonar pins
#define SONAR1_TRIGGER 22
#define SONAR1_ECHO 23
#define SONAR2_TRIGGER 24
#define SONAR2_ECHO 25
#define SONAR3_TRIGGER 26
#define SONAR3_ECHO 27
#define SONAR4_TRIGGER 28
#define SONAR4_ECHO 29
#define SONAR5_TRIGGER 30
#define SONAR5_ECHO 31
#define SONAR6_TRIGGER 32
#define SONAR6_ECHO 33

//Declaring some sonar variables
#define MAXIMUM_SONAR 200000


//Create sonars
NewPing sonar1(SONAR1_TRIGGER, SONAR1_ECHO, MAXIMUM_SONAR);
NewPing sonar2(SONAR2_TRIGGER, SONAR2_ECHO, MAXIMUM_SONAR);
NewPing sonar3(SONAR3_TRIGGER, SONAR3_ECHO, MAXIMUM_SONAR);
NewPing sonar4(SONAR4_TRIGGER, SONAR4_ECHO, MAXIMUM_SONAR);
NewPing sonar5(SONAR5_TRIGGER, SONAR5_ECHO, MAXIMUM_SONAR);
NewPing sonar6(SONAR6_TRIGGER, SONAR6_ECHO, MAXIMUM_SONAR);

//Store ultrasonic values
int sonarValue1 = 0;
int sonarValue2 = 0;
int sonarValue3 = 0;
int sonarValue4 = 0;
int sonarValue5 = 0;
int sonarValue6 = 0;


//Flick Switch variables
int flickSwitchPin = A0;
int flickSwitchPre;
bool flickSwitch;

byte relay = 53;


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
  RCorAI();
  //RC();
}


void RCorAI() {
  flickSwitchStatus();
  if (flickSwitch == true) {
    AI();
  }
  else {
    RC();
  }
}


void RC() {
  //Serial.println("This function will convert all the remote control values");
  //delay(printDelay);
  mapRC();
  actRC();
}


void AI() {
  Serial.println("This function will make the wheelchair autonomous");
  delay(printDelay);
  pingSonar();
}


void flickSwitchStatus() {
  flickSwitchPre = analogRead(flickSwitchPin);
  if (flickSwitchPre == 0) {
    flickSwitch = true;
  }
  else {
    flickSwitch = false;
  }
#ifdef DEBUG_FLICKSWITCH
  if (DEBUG_FLICKSWITCH == true) {
    printSpacer();
    if (flickSwitch == true) {
      Serial.println("Wheelchair is set to Autonomous!");
      delay(printDelay);
    }
    else {
      Serial.println("Wheelchair is set to Remote Control!");
      delay(printDelay);
    }
  }
#endif
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
