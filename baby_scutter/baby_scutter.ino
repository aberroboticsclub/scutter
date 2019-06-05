#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 11
#define NUMPIXELS 2



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

//between 0 and 255
 
uint32_t skyBlue = pixels.Color(135, 206, 255);
uint32_t maize = pixels.Color(128, 158, 10);
uint32_t lavender = pixels.Color(88, 2, 163);
uint32_t seaFoam = pixels.Color(32, 178, 170);
uint32_t spring = pixels.Color(102, 205, 0);
uint32_t orange = pixels.Color(250, 20, 20);
uint32_t pink = pixels.Color(250, 0, 87);
uint32_t red = pixels.Color(128, 0, 0);

int group[8] = {lavender, pink, red, skyBlue, maize, seaFoam, spring, orange};




Servo left;
Servo right;


void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
  left.attach(9);
  right.attach(10);
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void loop() {
  /*left.write(120);
    right.write(70);
    delay(2000);
    left.write(90);
    right.write(90);
    delay(2000);*/


  for (int j = 0; j < 8; j++) {
    //pixels.setPixelColor(0, group[j]); // Moderately bright green color.
    //pixels.setPixelColor(1, group[j]);
    pixels.setPixelColor(0, orange);
    pixels.setPixelColor(1, orange);
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
  }
/*
  //blueooth serial code
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  */
}
