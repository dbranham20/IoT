/*
    Technology Incubator IoT Hackathon
    Winthrop University - Spring 2018
    
    Smart Map Project (2/2)
    This code was used for the photons using the door sensors. The photon sends data of whether or not the sensor went off for the smart map photon to grab it and adjust the map accordingly.
*/

#define LEDPIN D7
#define MOTIONPIN D6
#define DOORPIN D4

int motionSensorState = 0, lastMotionState=0;         
int doorSensorState = 0, lastDoorState=0; 

void setup() {
  pinMode(LEDPIN, OUTPUT);      
  pinMode(DOORPIN, INPUT_PULLUP);    
  pinMode(MOTIONPIN, INPUT);
  
}

void loop() {
  motionSensorState = digitalRead(MOTIONPIN);
  doorSensorState = digitalRead(DOORPIN);

  //Serial.println(sensorState);
  
/*  if (motionSensorState == LOW) {     
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    digitalWrite(LEDPIN, LOW); 
  }
  
  if (doorSensorState == LOW) {     
    digitalWrite(LEDPIN, HIGH);  
  } 
  else {
    digitalWrite(LEDPIN, LOW); 
  }
  */

  
 
  if (motionSensorState && !lastMotionState) {
   
  } 
  if (!motionSensorState && lastMotionState) {
       
//    Particle.publish("motion", "fishbowl");
      Particle.publish("motion", "bathroom door");
  }
  
  lastMotionState = motionSensorState;
  
  
  if (doorSensorState && !lastDoorState) {
//      Particle.publish("door", "fishbowl open");
        Particle.publish("door", "bathroom door open");
      digitalWrite(LEDPIN, LOW);
  } 
  if (!doorSensorState && lastDoorState) {
//       Particle.publish("door", "fishbowl closed");
        Particle.publish("door", "bathroom door closed");
       digitalWrite(LEDPIN, HIGH); 
  }
  
  lastDoorState = doorSensorState;
  
  

}  // end loop 
