/*
    Technology Incubator IoT 
    Winthrop University - Spring 2018
    
    Recycle Bin Project (2/2)
    this program adds a series of lights to a LED light strip to showcase when someone throws something away in the recycling bin. it awaits for an event sent from the photons attached to the recycling bins
*/
// This #include statement was automatically added by the Particle IDE.
#include <FastLED.h>
FASTLED_USING_NAMESPACE

const int NUM_LEDS = 150; // Number of LEDs on light strip
const int LED_DATA = D7;  // Pin on photon/breadboard
const int waveSize = 1;   // Size to be sent along light strip
CRGB leds[NUM_LEDS];

int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0;

int addr = 10;
uint16_t value = 0;

int recycledTotal = 0;
uint8_t animateNum = 0;

// Cloud Variables
int analogValue = 5;

void setup() {
    FastLED.addLeds<NEOPIXEL, LED_DATA>(leds, NUM_LEDS);
    
    // Set all lights to default black
    displayBlue();
    Particle.function("count", count); // Setup function
    EEPROM.put(addr, value);
    
    // Cloud functions
    Particle.variable("analogvalue", analogValue);
    
    Particle.subscribe("recycle", myHandler);
}

void loop() {
    displayBluePulse();
}

int count(String command) {
    
    recycledTotal = atoi(command);
    animateNum = 1;
    return 1;
    
}

void ledAnimator() {
    EEPROM.get(addr, value);
    for (int x = 0; x < (NUM_LEDS - analogValue); x++) {
        delay(10);
        leds[x] = CRGB::Green;
        leds[max(0, x - waveSize)] = CRGB::Black;
        FastLED.show();
    }
    
    recycledTotal++;
    value++;
    EEPROM.put(addr, value);
}

void displayTotalRecycled() {
    EEPROM.get(addr, value);
    for (int j = 1; j <= analogValue; j++) {
        leds[NUM_LEDS - j] = CRGB::Green;
        FastLED.show();
    }
}

void displayBlack() {
    //delay(300);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
        FastLED.show();
    }
}

void displayBlue() {
    //delay(300);
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB( 0, 155, 218);
        if(i < 25) {
            leds[i].setRGB( 255, 196, 36);
        }
        FastLED.show();
    }
}

void displayBluePulse() {
    for (int i = 0; i < NUM_LEDS; i++) 
    {
        delay(2);
        leds[i].setRGB( 0, 155, 218);
        if(i < 25) {
            leds[i].setRGB( 255, 196, 36);
        }
        leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if(brightness == 0 || brightness == 255)
    {
        fadeAmount = -fadeAmount ;
    }   
    // leds[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25].setRGB( 255, 196, 36);
    // delay(75);
    // FastLED.show();
}

void myHandler(const char *event, const char *data) {
    EEPROM.put(addr, value);
    displayTotalRecycled();
    ledAnimator();
    displayBlack();
    displayBlue();
    animateNum = 0;
    Particle.variable("analogvalue", analogValue);
    analogValue++;
    if(analogValue > 299) {
        analogValue = 5;
    }
}
