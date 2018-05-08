/*
    Technology Incubator IoT Hackathon
    Winthrop University - Spring 2018
    
    Recycling Bin Project (1/2)
    This code was used to track how many items were thrown into a recycling bin. attached to the photon is a sensor to keep track of when an item is thrown away. 
*/

// D7 is the onboard LED 
// D6 is the pin that the sensor is connected to
#define LEDPIN D7
#define SENSORPIN D6
 
// variable for reading the pushbutton status
int sensorState = 0, lastState=0;         
 
void setup() {
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);    
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT_PULLUP);     

  // Serial.begin(9600);
}
 
//poll to keep checking if something was thrown away
void loop(){
    
  //reads the sensor pin and outputs the result into sensorState variable
  sensorState = digitalRead(SENSORPIN);
  //digitalRead returns LOW if something was thrown away
  //else digitalRead returns HIGH
  
  //following if else statements lets the user know that the trash thrown out was successfully read by turning the onboard LED on
  if (sensorState == LOW) {     
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    digitalWrite(LEDPIN, LOW); 
  }
  
  //following if statements are used to stop from reading one item more then once
  if (sensorState && !lastState) {
    //Serial.println("Unbroken");
  } 
  if (!sensorState && lastState) {
    //Serial.println("Broken");
    Particle.publish("recycle", "1");
    delay(3000);
  }
  
  //update lastState with current state 
  lastState = sensorState;
}
