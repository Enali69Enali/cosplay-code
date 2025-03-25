#include <Adafruit_NeoPixel.h>
// The Adafruit_NeoPixel library allows easy control of addressable WS2812 (NeoPixel) LEDs using a microcontroller like an Arduino. 
// It manages color display, animations, and communication with the LED strip through a single data pin.

/*      Variables      */
int X = 33;               // number of LED on the headband
int led = 6;              // I/O of the led headband
const int bouton = 4;
int val = 0;
int rouge = 255;
int vert = 200;

/* Declare our NeoPixel strip object:
 *    Argument 1 = Number of pixels in NeoPixel strip
 *    Argument 2 = Arduino pin number (most are valid)
 *    Argument 3 = Pixel type flags, add together as needed:
 *        NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
 *        NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
 *        NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
 *        NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
 *        NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
*/
Adafruit_NeoPixel strip(X, led, NEO_GRB + NEO_KHZ800); 



void setup() {
  strip.begin();
  strip.show();             // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(bouton,INPUT);
}

void loop() {
  val = digitalRead(bouton); // When we received a signal we do an explosion effect
  if (val==LOW){
    int retard = 20;
    for (int k=0;k<=6;k++){
      vert = 230;
      rouge = 255;
      for (int j = 0;j<=200;j=j+20){
        vert = vert - 20 ;
        if (vert >0){
          for (int n=0;n<X;n++){
            strip.setPixelColor(n,rouge,vert,0);
            strip.show();
            delay(max(0,retard-k*5));
            }
          }
        Serial.println(vert);
      }
    for (int a = 0; a <= 255 ; a=a+20){
      rouge = rouge - 20;
      for (int m = 0;m<X;m++){
        strip.setPixelColor(m,max(rouge,0),0,0);
          strip.show();
          delay(max(0,retard-k*5-10));
        }
      }
    }
    for ( int h=0; h<8; h++){ // Final flashing effect
      for (int j=0;j<X;j++){
        strip.setPixelColor(j,255,100,0);
      }
      strip.show();
      delay(50);
      for(int t=0;t<X;t++){
      strip.setPixelColor(t,0,0,0);
      }
      strip.show();
      delay(50);
    }
  }      
}
