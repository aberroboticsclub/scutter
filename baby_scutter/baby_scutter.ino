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
int delayval = 1000; // delay for half a second

//between 0 and 255  RGB
 
uint32_t red = pixels.Color(128, 0, 0);
uint32_t orange = pixels.Color(200, 30, 0);
uint32_t yellow = pixels.Color(150, 60, 0);
uint32_t green = pixels.Color(102, 190, 0);
uint32_t lightblue = pixels.Color(32, 178, 170);
uint32_t darkblue = pixels.Color(0, 0, 255);
uint32_t purple = pixels.Color(180, 2, 160);
uint32_t pink = pixels.Color(150, 0, 70);


int group[8] = { red, orange, yellow, green, lightblue, darkblue, purple, pink};




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
   pixels.clear();
    pixels.setPixelColor(0, group[j]); // Moderately bright green color.
    pixels.setPixelColor(1, group[j]);
    //pixels.setPixelColor(0, pink);
    //pixels.setPixelColor(1, pink);
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
