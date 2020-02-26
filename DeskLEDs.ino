// A basic everyday NeoPixel strip test program.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6
#define LED_PIN2    5
#define LED_COUNT 27
 int state = LOW;
const int buttonPin = 2;    // the number of the pushbutton pin
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 60;    // the debounce time; increase if the output flickers
// Declare our NeoPixel strip object:
Adafruit_NeoPixel stripR(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
uint32_t colorR = (255,0,0);
int changestate;
int statecount;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  stripR.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  stripR.show();            // Turn OFF all pixels ASAP
  stripR.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
 
}

void loop() {
  
    for(int i=0; i<stripR.numPixels(); i++) { 
        stripR.setPixelColor(i, 50, 150, 0);
      }
      stripR.show();
      delay(100);
    for(int i=0; i<stripR.numPixels(); i++) { 
        int GreenHolder = 180;
        int RedHolder = 110;
        GreenHolder = random(100,GreenHolder);
        RedHolder = random(20,RedHolder);
        stripR.setPixelColor(i, RedHolder, GreenHolder, 10);
      }
      stripR.show();
      delay(100);
  }


  
  

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void offState(uint32_t color, int wait) {
  int d = 0;
  for(int i=0; i<stripR.numPixels(); i++) { 
    if(i>4){
      stripR.setPixelColor(d,0);
      d = d+1;
      stripR.show(); 
    }
    //stripW.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    stripR.show();                          //  Update strip to match
    delay(10); 
  }
}

void button(){
  delay(1);
  if(digitalRead(2) == LOW){
    if(state==LOW){
      state=HIGH;
    }
    else{
    state=LOW;
    }
  }
 }


void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<stripR.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / stripR.numPixels());
      stripR.setPixelColor(i, stripR.gamma32(stripR.ColorHSV(pixelHue)));      
    }
    stripR.show(); 
    delay(wait);  
    
  }
}

//void brighten() {
//  uint16_t i, j;
//  for (j = 20; j < 200; j++) {
//    for (i = 0; i < stripR.numPixels(); i++) {
//      stripR.setPixelColor(i, j, 0, 0);
//      stripW.setPixelColor(i, j, j+10, j+10);
//    }
//    stripR.show();
//    stripW.show();
//    delay(1);
//  }
//  //delay(1500);
//}
//
//// 255 to 0
//void darken() {
//  uint16_t i, j;
//  for (j = 200; j > 20; j--) {
//    for (i = 0; i < stripR.numPixels(); i++) {
//      stripR.setPixelColor(i, j, 0, 0);
//      stripW.setPixelColor(i, j, j+10, j+10);
//    }
//    stripR.show();
//    stripW.show();
//    delay(1);
//  }
//}
