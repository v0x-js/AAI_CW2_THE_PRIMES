//ultimatrix script for NFC, Piezo pressure and led ring
//code for NFC reading based off of code found in PN532 Example library
//____________________________________for the librarys__________________________________________
//NFC Lirbary
#include <Wire.h>
#include <Adafruit_PN532.h>

//neopixel library
#include <Adafruit_NeoPixel.h>

//______________________________________Definitions______________________________________________



//NFC Definitions, defining the pins for the NFC Reader
#define PN532_IRQ (2)
#define PN532_RESET (3)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET); //defining the relationship/connection between the arduino board and the PN532


//NeoPixel LED Definitions----------------------------------------------------------------
#define LED_PIN 6
#define LED_COUNT 16
bool flashOnce = false;
bool idle = true;

// create function for the LED ring
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //number of LEDs on ring, pin connection, define specific model (RGBW), define data rate


//Piezo Definitons------------------------------------------------------------------------
#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
bool Pressed = false; //variable to say if piezo is being pushed or released
bool piezoPrevState = false;  //allows for comparison to previous state
bool piezoStateChange = false; // has there been a change in the state - true or false

//-----------------------------------------------------------------------------------------

//______________________________________Setup_________________________________________________

void setup() {

  //LED Ring Setup------------------------------------------------------------------------------
  ring.begin(); //start the ring function
  ring.show(); //set up ability for LEDs to display
  ring.setBrightness(50); //can go up to 255


  //NFC/RFID Setup------------------------------------------------------------------------------
  Serial.begin(115200); //Initialises the serial communication with the computer
  nfc.begin(); //begin nfc function


 //constant check for nfc board being connected to notify of error
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Cannot find PN532 board");
    while(1);
  }
}

void idleLED(){
  for(int i = 0; i < ring.numPixels(); i++){
  ring.setPixelColor(i, ring.Color(0, 225, 0));
  ring.show();
  delay(100);
  }
  delay(100);
  //for loop that runs for however many pixel leds there is (16 in this case), runs all individual LEDs sequentially and turns them off in the same order as previous loop
  for(int j = 0; j < ring.numPixels(); j++){
    ring.setPixelColor(j, ring.Color(0, 0, 0));
    ring.show();
    delay(100);
  }
}

void selectedLED(uint32_t color) {
  
   if (flashOnce != true) {

      ring.fill(color);
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 0));
      ring.show();
      delay(150);

      ring.fill(color);
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 0));
      ring.show();
      delay(150);
      flashOnce = true;
    }
  
    for(int i = 0; i < ring.numPixels(); i++){
      ring.setPixelColor(i, color);
      ring.show();
      delay(100);
    }
    delay(100);
    for(int i = 0; i < ring.numPixels(); i++){
      ring.setPixelColor(i, ring.Color(0, 0, 0));
      ring.show();
      delay(100);
    }
  }



//_____________________________________Main Code___________________________________________________
void loop() {
  // put your main code here, to run repeatedly:

  //Idle LED Ring------------------------------------------------------------------------------------------------------
  
  idleLED();


  //NFC Code (Reading and printing the UID)-----------------------------------------------------------------------------

  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0 }; //creates variable to store the tags UID
  uint8_t uidLength; //finds the legnth of the UID

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

//Logic system Depending on tags UID----------------------------------------------------------------------------
  
  //piezo state logic -------------------------------------------------------------------------------------------------
  val = analogRead(0); //reads the current value of the piezo

  if ( val > 3 ) { //checks if the current value is above the threshold
    Pressed = true;
    piezoStateChange = true;
  }

  if ( val < 3 ) {
    Pressed = false;
    piezoStateChange = true;
  }
  

//-----------------------------------------------------------------------------------------------------------------------------

  if ((uid == "(Place UID Here)") && (piezoStateChange == true) &&(piezoStateChange == true)) {

    selectedLED(ring.Color(225, 165, 0));

    //Sends message to max of what input to use
    Serial.println(1);
    delay(300);

    //LED Rings flash between Orange and white
  }

  else if (uid == "(Place UID Here)" && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
    Serial.println(2);
    delay(300);

  }

  else if (uid == "(Place UID Here)" && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
    Serial.println(2);
    delay(300);
  }
}

