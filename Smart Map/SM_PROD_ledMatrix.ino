/*
    Technology Incubator IoT Hackathon
    Winthrop University - Spring 2018
    
    Smart Map Project (1/2)
    This code was used to create the LED matrix that displays the map of the space we used. 
*/

// This #include statement was automatically added by the Particle IDE.
#include <SparkIntervalTimer.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_mfGFX.h>

// This #include statement was automatically added by the Particle IDE.
#include <RGBmatrixPanel.h> // Hardware-specific library

// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

//#include "math.h"

// Modify for version of RGBShieldMatrix that you have
// HINT: Maker Faire 2016 Kit and later have shield version 4 (3 prior to that)
//
// NOTE: Version 4 of the RGBMatrix Shield only works with Photon and Electron (not Core)
//#define RGBSHIELDVERSION		4

/** Define RGB matrix panel GPIO pins **/

//#if (RGBSHIELDVERSION == 4)		// Newest shield with SD socket onboard
//	#warning "new shield"
	#define CLK	D6
	#define OE	D7
	#define LAT	A4
	#define A  	A0
	#define B  	A1
	#define C  	A2
	#define D	A3

/****************************************/

//RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void doorHandler(const char *event, const char *data){
 
    if(strcmp(data, "fishbowl open")==0)
    {
        matrix.drawLine(39,19,39,22, matrix.Color333(0,255,0)); //fishbowl door open = red       
        matrix.updateDisplay();
    }
    else if(strcmp(data, "fishbowl closed")==0)
    {
        matrix.drawLine(39,19,39,22, matrix.Color333(255,0,0)); //fishbowl door closed = green       
        matrix.updateDisplay();
    } 

    if(strcmp(data, "back door open")==0)
    {
        matrix.drawLine(62,24,62,27, matrix.Color333(0,255,0)); //backdoor
        matrix.updateDisplay();
    }
    else if(strcmp(data, "back door closed")==0)
    {
        matrix.drawLine(62,24,62,27, matrix.Color333(255,0,0)); //backdoor
        matrix.updateDisplay();
    }

    if(strcmp(data, "conference door open")==0)
    {
        matrix.drawLine(11,20,11,24, matrix.Color333(0,255,0));
        matrix.updateDisplay();
    }
    else if(strcmp(data, "conference door closed")==0)
    {
        matrix.drawLine(11,20,11,24, matrix.Color333(255,0,0));
        matrix.updateDisplay();
    }    
    
    if(strcmp(data, "front door open")==0)
    {
        matrix.drawLine(11,14,11,17, matrix.Color333(0,255,0));
        matrix.updateDisplay();
    }
    else if(strcmp(data, "front door closed")==0)
    {
        matrix.drawLine(11,14,11,17, matrix.Color333(255,0,0));
        matrix.updateDisplay();
    }   
    if(strcmp(data, "bathroom door open")==0)
    {
        matrix.drawLine(20,13,23,13, matrix.Color333(0,255,0));
        matrix.updateDisplay();
    }
    else if(strcmp(data, "bathroom door closed")==0)
    {
        matrix.drawLine(20,13,23,13, matrix.Color333(255,0,0));
        matrix.updateDisplay();
    }
    
    else
    {
        
    }

}

void motionHandler(const char *event, const char *data){

    bool find_fishbowl= false; 

    if(strcmp(data, "fishbowl")==0)
    {
        matrix.fillRect(40,19,15,9, matrix.Color333(0,250,100));
    }
    else if(strcmp(data, "conference")==0)
    {
        matrix.fillRect(2,19,9,9, matrix.Color333(0,250,100));
    }
    else if(strcmp(data, "front door")==0) 
    {
        for(int x = 0; x < 5; x++)
        {
            matrix.fillRect(9,14,2,4, matrix.Color333(255,255,0));
            delay(100);
            matrix.fillRect(9,14,2,4, matrix.Color333(0,0,0));
        }
    
    }
    else if(strcmp(data, "back door")==0)
    {
        matrix.fillRect(56,18,6,10, matrix.Color333(0,250,100)); //backdoor
    }
    else
    {
        matrix.fillRect(56,18,6,10, matrix.Color333(0,0,0)); //backdoor
        matrix.fillRect(40,19,15,9, matrix.Color333(0,0,0)); //fishbowl
        matrix.fillRect(2,19,9,9, matrix.Color333(0,0,0)); //conference
    }  
    
    matrix.updateDisplay();

}

void setup() {
    
    matrix.begin();
    
    //Outline of Map
    matrix.drawLine(1,13,1,28, matrix.Color333(255,255,255)); //left wall
    matrix.drawLine(62,3,62,28, matrix.Color333(255,255,255)); //right wall
    matrix.drawLine(18,3,61,3, matrix.Color333(255,255,255)); //Top wall
    matrix.drawLine(1,28,61,28, matrix.Color333(255,255,255)); //bottom wall
    matrix.drawLine(1,13,39,13, matrix.Color333(255,255,255)); //kitchen wall
    matrix.drawLine(11,13,11,18, matrix.Color333(255,255,255));
    
    //Fishbowl
    matrix.drawLine(39,18,55,18, matrix.Color333(255,255,255));
    matrix.drawLine(39,18,39,28, matrix.Color333(255,255,255));
    matrix.drawLine(55,18,55,28, matrix.Color333(255,255,255));

    //Office
    matrix.drawLine(18,18,31,18, matrix.Color333(255,255,255)); //Top wall
    matrix.drawLine(18,18,18,28, matrix.Color333(255,255,255)); //left wall
    matrix.drawLine(31,18,31,28, matrix.Color333(255,255,255)); //right wall
    
    //Bathroom and Kitchen
    matrix.drawLine(39,3,39,13, matrix.Color333(255,255,255));
    matrix.drawLine(18,3,18,13, matrix.Color333(255,255,255));
    matrix.drawLine(25,3,25,13, matrix.Color333(255,255,255));
    
    //Conference Room
    matrix.drawLine(1,18,11,18, matrix.Color333(255,255,255)); //Top wall
    matrix.drawLine(11,18,11,28, matrix.Color333(255,255,255)); //Right wall
    matrix.drawLine(6,13,6,17, matrix.Color333(255,255,255));
    
    //Miscellaneous
    matrix.drawLine(36,13,38,13, matrix.Color333(0,0,0)); //Kitchen Opening
    matrix.drawLine(7,13,10,13, matrix.Color333(0,0,0));


    //Ti
    matrix.drawLine(4,4,10,4, matrix.Color333(0,250,100)); //T
    matrix.drawLine(4,5,10,5, matrix.Color333(0,250,100));
    matrix.drawLine(6,2,6,10, matrix.Color333(0,250,100));
    matrix.drawLine(8,2,8,10, matrix.Color333(0,250,100));
    matrix.drawLine(7,2,7,10, matrix.Color333(0,250,100));
    matrix.drawPixel(11,5, matrix.Color333(0,250,100));
    
    matrix.drawLine(10,6,10,10, matrix.Color333(0,200,225)); //i
    matrix.drawLine(11,6,11,10, matrix.Color333(0,200,225));
    matrix.drawLine(10,2,11,2, matrix.Color333(250,250,0));
    matrix.drawPixel(11,3, matrix.Color333(250,250,0));
    
    //Doors
    //matrix.drawLine(7,13,10,13, matrix.Color333(0,255,0));
    matrix.drawLine(62,24,62,27, matrix.Color333(255,0,0));
    matrix.drawLine(31,19,31,22, matrix.Color333(255,0,0)); //office
    matrix.drawLine(39,19,39,22, matrix.Color333(255,0,0)); //fishbowl
    matrix.drawLine(20,13,23,13, matrix.Color333(255,0,0)); //bathroom
    matrix.drawLine(11,20,11,24, matrix.Color333(255,0,0)); //conference room
    matrix.drawLine(11,14,11,17, matrix.Color333(255,0,0)); //front door 
    
    
    
    matrix.updateDisplay();
    delay(2000);

    Particle.subscribe("door", doorHandler);
    Particle.subscribe("motion", motionHandler);

}

void loop() {
  // do nothing

}
