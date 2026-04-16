#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
bool Pressed = false; //variable to say if piezo is being pushed or released
bool piezoPrevState = false;  //allows for comparison to previous state
bool piezoStateChange = false; // has there been a change in the state - true or false

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0); //reads the current value of the piezo

  if ( val >= PIEZOTHRESHOLD ) { //checks if the current value is above the threshold
    Pressed = true;
    if (Pressed != piezoPrevState) { //if the comparison is different from the current bool value a state change has occured
      piezoStateChange = true;
      piezoPrevState = Pressed; //sets the prev pressed state value to the current pressed state value for comparison on the next time the main void loop loops
    }
  }
    //essiential the same as code above but in reverse for when the dial is released from the closed position
  else if ( val <= PIEZOTHRESHOLD ) {
    Pressed = true;
    if (Pressed == piezoPrevState) {
      piezoStateChange = false;
      piezoPrevState = Pressed;
    }
  }

  if (piezoStateChange == true) {
    print("Watch is pressed Down");
    Serial.write(1);
  }

  else if (piezoStateChange == false) {
    print("Watch is released");
    Serial.write(4);
  }



}

