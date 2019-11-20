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

//between 0 and 25  RGB
 
uint32_t red = pixels.Color(128, 0, 0);
uint32_t orange = pixels.Color(200, 30, 0);
uint32_t gold = pixels.Color(200, 70, 10);
uint32_t yellow = pixels.Color(150, 60, 0);
uint32_t green = pixels.Color(102, 190, 0);
uint32_t greenblue = pixels.Color(0, 40, 50);
uint32_t lightblue = pixels.Color(32, 178, 170);
uint32_t darkblue = pixels.Color(0, 0, 255);
uint32_t purple = pixels.Color(80, 2, 100);
uint32_t lightpurple = pixels.Color(180, 2, 160);
uint32_t pink = pixels.Color(150, 0, 70);
uint32_t redpink = pixels.Color(150, 0, 20);
uint32_t lightpink = pixels.Color(30, 0,  15);
uint32_t white = pixels.Color(100, 100, 100);

uint32_t pink1 = pixels.Color(150, 0, 10);
uint32_t pink2 = pixels.Color(150, 0, 20);
uint32_t pink3= pixels.Color(150, 0, 30);
uint32_t pink4 = pixels.Color(150, 0, 40);
uint32_t pink5 = pixels.Color(150, 0, 50);
uint32_t pink6 = pixels.Color(150, 0, 60);
uint32_t pink7 = pixels.Color(150, 0, 70);
uint32_t pink8 = pixels.Color(150, 0, 80);
uint32_t pink9 = pixels.Color(150, 0, 90);
uint32_t pink10 = pixels.Color(150, 0, 100);
uint32_t pink11 = pixels.Color(150, 0, 110);
uint32_t pink12 = pixels.Color(150, 0, 120);
uint32_t pink13 = pixels.Color(150, 0, 130);
uint32_t pink14 = pixels.Color(150, 0, 140);
uint32_t pink15 = pixels.Color(150, 0, 150);
uint32_t pink16 = pixels.Color(150, 0, 160);
uint32_t pink17 = pixels.Color(150, 0, 170);
uint32_t pink18 = pixels.Color(150, 0, 180);
uint32_t pink19 = pixels.Color(150, 0, 190);
uint32_t pink20 = pixels.Color(150, 0, 200);

uint32_t blue1 = pixels.Color(0, 0, 10);
uint32_t blue2 = pixels.Color(0, 0, 20);
uint32_t blue3= pixels.Color(0, 0, 30);
uint32_t blue4 = pixels.Color(0, 0, 40);
uint32_t blue5 = pixels.Color(0, 0, 50);
uint32_t blue6 = pixels.Color(0, 0, 60);
uint32_t blue7 = pixels.Color(0, 0, 70);
uint32_t blue8 = pixels.Color(0, 0, 80);
uint32_t blue9 = pixels.Color(0, 0, 90);
uint32_t blue10 = pixels.Color(0, 0, 100);
uint32_t blue11 = pixels.Color(0, 0, 110);
uint32_t blue12 = pixels.Color(0, 0, 120);
uint32_t blue13 = pixels.Color(0, 0, 130);
uint32_t blue14 = pixels.Color(0, 0, 140);
uint32_t blue15 = pixels.Color(0, 0, 150);
uint32_t blue16 = pixels.Color(0, 0, 160);
uint32_t blue17 = pixels.Color(0, 0, 170);
uint32_t blue18 = pixels.Color(0, 0, 180);
uint32_t blue19 = pixels.Color(0, 0, 190);
uint32_t blue20 = pixels.Color(0, 0, 200);
//int group[8] = { red, orange, yellow, green, lightblue, darkblue, purple, pink};





void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
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
    //pixels.clear();
    //pixels.setPixelColor(0, group[j]);
    //pixels.setPixelColor(1, group[j]);
//    pixels.setPixelColor(0, e); //Single colour practice
//    pixels.setPixelColor(1, e);
//    pixels.show();
      
    pixels.setPixelColor(0,red);
    pixels.setPixelColor(1,red);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,orange);
    pixels.setPixelColor(1,orange);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,gold);
    pixels.setPixelColor(1,gold);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,yellow);
    pixels.setPixelColor(1,yellow);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,green);
    pixels.setPixelColor(1,green);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,lightblue);
    pixels.setPixelColor(1,lightblue);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,greenblue);
    pixels.setPixelColor(1,greenblue);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,darkblue);
    pixels.setPixelColor(1,darkblue);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,purple);
    pixels.setPixelColor(1,purple);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,lightpurple);
    pixels.setPixelColor(1,lightpurple);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,pink);
    pixels.setPixelColor(1,pink);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,redpink);
    pixels.setPixelColor(1,redpink);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,lightpink);
    pixels.setPixelColor(1,lightpink);
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(0,white);
    pixels.setPixelColor(1,white);
    pixels.show();
    delay(delayval);
//
//    pixels.setPixelColor(0,lightblue);
//    pixels.setPixelColor(1,lightblue);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,greenblue);
//    pixels.setPixelColor(1,greenblue);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,darkblue);
//    pixels.setPixelColor(1,darkblue);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,purple);
//    pixels.setPixelColor(1,purple);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,lightpurple);
//    pixels.setPixelColor(1,lightpurple);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,pink);
//    pixels.setPixelColor(1,pink);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,redpink);
//    pixels.setPixelColor(1,redpink);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,lightpink);
//    pixels.setPixelColor(1,lightpink);
//    pixels.show();
//    delay(delayval);
//    pixels.setPixelColor(0,white);
//    pixels.setPixelColor(1,white);
//    pixels.show();
//    delay(delayval);
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
