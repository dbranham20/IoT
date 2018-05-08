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
const int NUM_LEDS = 150;
const int DATA = D7;

int mode = 0;
unsigned long changed = 0;

//led array
CRGB leds[NUM_LEDS];

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
    //create led object
    FastLED.addLeds<NEOPIXEL, DATA>(leds,NUM_LEDS);
        
    //we want to run this when door sensor is open
    Particle.subscribe("door", doorHandler);
}

void loop(){
    
    //do nothing unless mode is 1
    if(mode == 1){
        
        //move everything down 1
        for(int current = NUM_LEDS - 1; current > 0; current--){
            leds[current] = leds[current-1];
        }
        
        //make a raindrop randomly
        if(((rand() % 30) == 1)){
            leds[0].setRGB(255,255,255);
            leds[0].fadeLightBy(235);
            leds[1].setRGB(255,255,255);
            leds[1].fadeLightBy(225);
            leds[2].setRGB(255,255,255);
            leds[2].fadeLightBy(215);
            leds[3].setRGB(255,255,255);
            leds[3].fadeLightBy(200);
            leds[4].setRGB(255,255,255);
            leds[4].fadeLightBy(185);
        }
        else{
            leds[0].setRGB(0,0,0);
        }
    
        //following is a timer. Go on for 20 seconds and change mode to off
        if(millis() - changed > 20000)
        {
            mode=0;
            
            //make all leds to blakc
            for(int current = 0; current < NUM_LEDS; current++){
                leds[current].setRGB(0,0,0);
            }
        }
        
        //output result
        FastLED.show();
        
        //20 milisecond delay
        delay(20); 
    }
}
