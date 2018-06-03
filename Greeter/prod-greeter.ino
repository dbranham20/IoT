/*
    Technology Incubator IoT 
    Winthrop University - Spring 2018
    
    Greeter Project (1/1)
    This program plays sounds to greet people as they enter a space.
*/
// S Dannelly
// June 1, 2018

// info pulled from cloud
//     hall and door statuses
int hallstatus;
int doorstatus;
int empty = 1;
int busy = 2;
int open = 1;
int closed = 2;

// output pins
int pin_in_msg = D1;  // connected to trigger 1 on sound board
int pin_out_msg = D2; // connected to trigger 2 on sound board


// **************************************************
void setup() 
{
   // subsribe to cloud data
   Particle.subscribe("door", doorHandler, MY_DEVICES);
   Particle.subscribe("motion", motionHandler, MY_DEVICES);
 
   // nothing is happening initially
   hallstatus = empty;
   doorstatus = closed;

   // turn all the sound tiggers to high
   pinMode (pin_in_msg,  OUTPUT);
   pinMode (pin_out_msg, OUTPUT);
   
   // pins go LOW to trigger a sound
   digitalWrite (pin_in_msg, HIGH);
   digitalWrite (pin_out_msg, HIGH);
   
   // use D7 LED for debugging
   pinMode(D7, OUTPUT);
   digitalWrite (D7, LOW);
}

// ******************************************************
// ******************************************************

void loop() 
{
    if ((hallstatus == empty) && (doorstatus == open))  // no hall, but door
       leaving();
    else if ((hallstatus == busy) && (doorstatus == open))  // hall then door
       entering();
}

// ******************************************************
// ******************************************************

void doorHandler (const char *event, const char *data)
{
   if (strcmp(data, "front door open") == 0)
      doorstatus = open;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * 
void motionHandler (const char *event, const char *data)
{
    if (strcmp (data, "front door") == 0)
       hallstatus = busy;
}

// ****************************************************
void clearStatus()
{
    doorstatus = closed;
    hallstatus = empty;
}

// ***************************************************
// ******************************************************

void entering ()
{
    // when someone enters, 
    //      set a pin low to trigger sound
    
    digitalWrite (pin_in_msg, LOW);
    delay (500);
    digitalWrite (pin_in_msg, HIGH);
    delay (500);
    
    // debugging - fast flashing
    for (int i=0; i<10; i++)
    {  
        digitalWrite (D7, HIGH);
        delay (200);
        digitalWrite (D7, LOW);
        delay (200);
    }
    
    // don't immediately retrigger
    delay(3000);
    clearStatus();
}

// ***************************************************

void leaving ()
{
    // when someone leaves, 
    //      set a pin low to trigger sound

    digitalWrite (pin_out_msg, LOW);
    delay (500);
    digitalWrite (pin_out_msg, HIGH);
    delay (500);
    
    // debugging - slow flashing
    for (int i=0; i<4; i++)
    {  
        digitalWrite (D7, HIGH);
        delay (500);
        digitalWrite (D7, LOW);
        delay (500);
    }
    
    // don't immediately retrigger
    delay(3000);
    clearStatus();
}

