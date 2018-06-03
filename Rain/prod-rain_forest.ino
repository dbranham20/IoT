/*
    Technology Incubator IoT 
    Winthrop University - Spring 2018
    
    LED Strip Rain Project (1/1)
    This program awaits for an external variable to tell it when to put on a "rain show" using Adafruit LED light strips. 
*/

// This #include statement was automatically added by the Particle IDE.
#include <FastLED.h>
FASTLED_USING_NAMESPACE

//constants about our hardware
const int NUM_LEDS = 300;
const int DATA1 = D4;
const int DATA2 = D0;
const int MOTIONPIN = D5;

int mode = 1;
unsigned long changed = 0;
int motionState = 0;

//led array
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
//if door is opened
void doorHandler(const char *event, const char *data){
    //make sure its the door we want
    if(strcmp(data, "front door open")==0){
        mode = 1;
        //keep track of when it was opened
        changed = millis();
    }
}

void setup(){
    //create led object(s)
    FastLED.addLeds<NEOPIXEL, DATA1>(leds1,NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA2>(leds2,NUM_LEDS);
        
    //we want to run this when door sensor is open
    Particle.subscribe("door", doorHandler);
    
    pinMode(MOTIONPIN, INPUT);

}

void loop(){        //20 milisecond delay
        delay(20); 
 //   motionState = digitalRead(MOTIONPIN); 
  //  if(motionState){
   //     mode = 1;
   //     changed = millis();
  //  }
    //do nothing unless mode is 1
    if(mode == 1){
        
        //move everything down 1
        for(int current = NUM_LEDS - 1; current > 0; current--){
            leds1[current] = leds1[current-1];
            leds2[current] = leds2[current-1];
        }
        
        //make a raindrop randomly
        if(((rand() % 30) == 1)){
            leds1[0].setRGB(255,255,255);
            leds1[0].fadeLightBy(235);
            leds1[1].setRGB(255,255,255);
            leds1[1].fadeLightBy(225);
            leds1[2].setRGB(255,255,255);
            leds1[2].fadeLightBy(215);
            leds1[3].setRGB(255,255,255);
            leds1[3].fadeLightBy(200);
            leds1[4].setRGB(255,255,255);
            leds1[4].fadeLightBy(185);
            
        }
        else{
            leds1[0].setRGB(0,0,0);
        }
        if(((rand() % 30) == 1)){
            leds2[0].setRGB(255,255,255);
            leds2[0].fadeLightBy(235);
            leds2[1].setRGB(255,255,255);
            leds2[1].fadeLightBy(225);
            leds2[2].setRGB(255,255,255);
            leds2[2].fadeLightBy(215);
            leds2[3].setRGB(255,255,255);
            leds2[3].fadeLightBy(200);
            leds2[4].setRGB(255,255,255);
            leds2[4].fadeLightBy(185);  
        }
        else{
            leds2[0].setRGB(0,0,0);
        }
        
        //following is a timer. Go on for 20 seconds and change mode to off
        if(millis() - changed > 20000)
        {
            mode=0;
            
            //make all leds to blakc
            for(int current = 0; current < NUM_LEDS; current++){
                leds1[current].setRGB(0,0,0);
                leds2[current].setRGB(0,0,0);
            }
        }
        
        //output result
        FastLED.show();
    }
}
