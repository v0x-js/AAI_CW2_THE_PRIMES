#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
bool Pressed = false; //variable to say if piezo is being pushed or released
bool piezoPrevState = false;  //allows for comparison to previous state
bool piezoStateChange = false; // has there been a change in the state - true or false

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0); //reads the current value of the piezo

  if ( val > 5 ) { //checks if the current value is above the threshold
    Pressed = true;
    piezoStateChange = true;
  }


  if ( val < 5 ) {
    Pressed = false;
    piezoStateChange = true;
  }
  

  if ((Pressed == true) && (piezoStateChange == true) ) {
    
    Serial.println(1); 
    delay(300); 
  }
}

