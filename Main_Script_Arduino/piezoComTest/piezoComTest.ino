#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
bool Pressed = false; //variable to say if piezo is being pushed or released
bool piezoPrevState = false;  //allows for comparison to previous state
bool piezoStateChange = false; // has there been a change in the state - true or false
bool piezoRelease = false; 

bool StopData = false; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0); //reads the current value of the piezo

  if ( val > 5 ) { //checks if the current value is above the threshold
    Pressed = true;
    if (Pressed != piezoPrevState) { //if the comparison is different from the current bool value a state change has occured
      piezoStateChange = true;
      piezoRelease = false; 
    }
  //  piezoPrevState = Pressed; //sets the prev pressed state value to the current pressed state value for comparison on the next time the main void loop loops
  }
    //essiential the same as code above but in reverse for when the dial is released from the closed position
  if ( val < 5 ) {
    Pressed = false;
    if (Pressed == piezoPrevState) {
      piezoStateChange = true;
      piezoRelease = true; 
    }
  }
<<<<<<< Updated upstream

  if ((Pressed = true) && (piezoStateChange = true) && (piezoRelease = false) && (StopData = false)) {
    
    Serial.println(1);
    StopData = true; 
  }

  if (StopData = true) {
    piezoStateChange = false; 
  } 


  if ((Pressed = false) && (piezoStateChange = true) && (piezoRelease = true) && (StopData = true)) {
  
    Serial.println(4); 
    StopData = false; 
  }
  
  if (StopData = false) {
    piezoStateChange = false;
  }


=======
  if ((Pressed == true) && (piezoStateChange == true)) {
    Serial.println(1);
    delay(300);
  } 
>>>>>>> Stashed changes
}

