/*
    Technology Incubator IoT 
    Winthrop University - Spring 2018
    
    LED Strip 1D Game Project (1/1)
    this program is a "pong" game for the LED light strip.  
*/
// This #include statement was automatically added by the Particle IDE.
#include <FastLED.h>

// This #include statement was automatically added by the Particle IDE.
#include <FastLED.h>
#include <stdlib.h>  

FASTLED_USING_NAMESPACE


//initialize variables
const int NUM_LEDS=150; //how many leds my light strip has
CRGB leds[NUM_LEDS]; 

const int LED_DATA = D5; //where is my led light strip getting its data

unsigned long previousMillisP1 = 0;  
unsigned long previousMillisP2 = 0;  
unsigned long p1Timeout = 0; 
unsigned long p2Timeout = 0;

const long generalTimeout = 500;
const long activeInterval = 1000;

int OFFSET = 30;
int direction = 1; //1 is Right | -1 is left

bool buttonOneCheck = true;
bool buttonTwoCheck = true;

bool game = false;
int winner = 0; //0 is none, 1 is 1, 2 is 2

uint16_t paddleSize = 10;

bool paddleOneActive = false;
bool paddleTwoActive = false;

int maxBallSpeed = 10;
int minBallSpeed = 1;

uint16_t ballSize = 2;
uint16_t ballSpeed = 1; // rand() % maxBallSpeed + minBallSpeed;

int ballPlace = paddleSize;
int ballEnd = ballPlace + ballSize;

//initialize default colors
CRGB::HTMLColorCode default2PaddleColor = CRGB::White;
CRGB::HTMLColorCode default1PaddleColor = CRGB::Green;
CRGB::HTMLColorCode activePaddleColor = CRGB::Blue;
CRGB::HTMLColorCode ballColor = CRGB::Red;
CRGB::HTMLColorCode defaultBackground = CRGB::Black;     
CRGB::HTMLColorCode winningColor = CRGB::Yellow;

//eli colors
CRGB::HTMLColorCode blue = CRGB::Blue;
CRGB::HTMLColorCode black = CRGB::Black;
CRGB::HTMLColorCode white = CRGB::White;


//INACTIVE ANIMATION VARIBALES AND FUNCTIONS
unsigned long lastAnimation = 0;
int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0;

void displayBluePulse() {
    for (int i = 0; i < NUM_LEDS; i++){
        leds[i].setRGB(0, 155, 218);
        if(i < OFFSET) {
            leds[i].setRGB(0, 0, 0);
        }
        if (i >= OFFSET && i <= OFFSET + 25) {
            leds[i].setRGB(255,196,36);
        }
        leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if(brightness == 0 || brightness == 255)
    {
        fadeAmount = -fadeAmount ;
        lastAnimation = millis();
    }   
    // leds[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25].setRGB( 255, 196, 36);
    // delay(75);
    // FastLED.show();
}

//END INACTIVE ANIMATION VARIBALES AND FUNCTIONS


void setup() {
    pinMode(LED_DATA, OUTPUT);
    FastLED.addLeds<NEOPIXEL, LED_DATA>(leds, NUM_LEDS); 
    //FastLED.show();
    //theReset("");
    Particle.function("paddleOne", paddleOne);
    Particle.function("paddleTwo",paddleTwo);
    Particle.function("theReset",theReset);
    
    displayBluePulse();
}

void loop () {
  if(game){ //while a game is in progress....
      processPaddles(); 
      updateBallLocation();
      
      if(winner != 0)
      {
          processWinner();
          FastLED.show();
          delay(2000);
      }
      
      FastLED.show();
      delay(50);
  }
  else{
      if(lastAnimation + 15000 < millis()){ // in and out every 10 seconds
        displayBluePulse();
        delay(100); 
      }
  }
}

//this function processes paddle hits
void processPaddles(){
    if(paddleOneActive == true && millis() - previousMillisP1 > activeInterval ){
        paddleOneActive = false;
        p1Timeout = millis () + generalTimeout;
        buttonOneCheck = true;
    }
    if(paddleTwoActive == true && millis() - previousMillisP2 > activeInterval ){
        paddleTwoActive = false;
        p2Timeout = millis () + generalTimeout;
        buttonTwoCheck = true;
    }
    
    for(int ct=OFFSET; ct< (OFFSET+paddleSize); ct++){
        if(paddleOneActive){
            leds[ct] = activePaddleColor;
        }
        else{
            leds[ct] = default1PaddleColor;
        }
    }
    for(int ct=NUM_LEDS - 1 ; ct >= NUM_LEDS - paddleSize; ct--){
        if(paddleTwoActive){
            leds[ct] = activePaddleColor;
        }
        else{
            leds[ct] = default2PaddleColor;
        }
    }    
}



void processWinner(){
    game = false;
      //P1 or P2 has won
  for(int ct=OFFSET; ct < NUM_LEDS/2; ct++){
      if(winner == 1){
          leds[ct] = winningColor;
          leds[ct+NUM_LEDS/2] = defaultBackground;
      }
      else{
          leds[ct] = defaultBackground;
          leds[ct+NUM_LEDS/2] = winningColor;
      }
  }

}

void updateBallLocation(){
    if(direction > 0){
        //going right
        if(ballPlace +  ballSize + ballSpeed >= NUM_LEDS - paddleSize - 1){
            if(paddleTwoActive){
                direction = -1;
                //maxBallSpeed + rand() % 1 + 0.1;
                //ballSpeed = rand() % maxBallSpeed + minBallSpeed;
		        ballSpeed += 1;
            }
            else{
                //P2 lose
                winner = 1; 
            }
        }
        else{
            ballPlace += ballSpeed;
            ballEnd = ballPlace + ballSize;
        }
    }
    else{
        //going left
        if(ballPlace - ballSpeed <= OFFSET + paddleSize){
            if(paddleOneActive){
                direction = 1;
                //ballSpeed = rand() % maxBallSpeed + minBallSpeed;
		ballSpeed += 1;
            }
            else{
                winner = 2;
            }
        }
        else{
            ballPlace -= ballSpeed;
            ballEnd = ballPlace + ballSize;
           
        }
    }

//CRGB::HTMLColorCode ballColor = CRGB::Red;
//CRGB::HTMLColorCode defaultBackground = CRGB::Black;     

    for(int ct=OFFSET + paddleSize; ct < NUM_LEDS - paddleSize; ct++) {
        if(ct < ballPlace || ct > ballEnd){
            leds[ct] = defaultBackground;
        }
        else{
            leds[ct] = ballColor;
        }
    }


    
}

int theReset(String extra) {
    game = true;
    direction = 1;//Right -1 is left
    winner = 0; //0 is none, 1 is 1, 2 is 2
    //maxBallSpeed + rand() % 1 + 0.1;
   // ballSpeed = rand() % maxBallSpeed + minBallSpeed;
    ballSpeed = 1;
    ballPlace = OFFSET + paddleSize;
    paddleOneActive = false;
    paddleTwoActive = false;
}

int paddleTwo(String extra) { 
    if (buttonTwoCheck == true){
        if (millis() > p2Timeout){
            paddleTwoActive=true;
            previousMillisP2 = millis();
            buttonTwoCheck = false;
        }

    }
}


int paddleOne(String extra) {
    if (buttonOneCheck == true) {
       if (millis() > p1Timeout){
            paddleOneActive=true;
            previousMillisP1 = millis();
            buttonOneCheck = false;
        }
        
    }
}

