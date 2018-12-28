#include <Mux.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 64

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 19

#define addr0 18
#define addr1 5
#define addr2 17
#define addr3 16

int ledThreshold = 11; //threshold level to trigger touch button
int numRead = 4;//set the number of read commands in read burst

CRGB leds[NUM_LEDS];

//Mux mux(2,3,4,5,A0); // initialise on construct... 
Mux mux; // ...or construct now, and call setup later

int analogPins[] = {4,13,12,14,27}; //byte 0 is number of defined pins to follow
byte counter = 0x0F;

void setup(){
  touch_pad_init();
  Serial.begin(115200);
  mux.setup(addr0, addr1, addr2, addr3,&analogPins[0]); // initialise on setup addr0, addr1, addr2, addr3, analog
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = 0x050500;
}

void loop(){
  int val[4];
  for (int j = 0; j < 4; j++)
  {
    val[j] = 0;
    for (int i = 0; i < numRead; i++)
    {
      val[j] = val[j] + mux.readTouch(counter,j);
    }
  }
  for (int j = 0; j < 4; j++)
  {
    val[j] = round(val[j]/numRead);
    if((counter==15) && (j==3))
    {
      Serial.println(val[j]); 
    }else{
      Serial.print(val[j]);
      Serial.print(", "); 
    }
    if (val[j] < ledThreshold)
      leds[(4*counter) + j] = 0x070000;
    else
      leds[(4*counter) + j] = 0x000007;
  }

  counter = (counter+1) & 0x0F;
  if (counter==0)
  {
    FastLED.show();
  }
  
}
