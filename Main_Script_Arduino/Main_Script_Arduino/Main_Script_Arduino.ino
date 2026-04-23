//ultimatrix script for NFC, Piezo pressure and led ring
//code for NFC reading based off of code found in PN532 Example library
//____________________________________for the librarys__________________________________________
//NFC Lirbary
#include <Wire.h>
#include <Adafruit_PN532.h>

//neopixel library
#include <Adafruit_NeoPixel.h>

//______________________________________Definitions______________________________________________



//NFC Definitions, defining the pins for the NFC Reader for i2c configuration
#define PN532_IRQ (2)
#define PN532_RESET (3)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET); //defining the relationship/connection between the arduino board and the PN532

uint8_t uidOptimus[] = {0x7A, 0xA1, 0x1A, 0xA3};
uint8_t uidHeatblast[] = {0xD6, 0x19, 0xF3, 0xFF};
uint8_t uidAlienX[] = {0xE2, 0x00, 0x10, 0x10};
uint8_t uidClear[] = {0xD6, 0xAB, 0xD6, 0xFF};

// Set to false by default
bool optimusMatch = false;
bool heatblastMatch = false;
bool alienXMatch = false;
bool clearMatch = false;


//NeoPixel LED Definitions----------------------------------------------------------------
#define LED_PIN 6
#define LED_COUNT 16
//bool flashOnce = false;
bool idle = true;

// create function for the LED ring
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //number of LEDs on ring, pin connection, define specific model (RGBW), define data rate


//Piezo Definitons------------------------------------------------------------------------
#define PIEZOTHRESHOLD 0.5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
 //variable to say if piezo is being pushed or released
//bool piezoPrevState = false;  //allows for comparison to previous state
 // has there been a change in the state - true or false

//-----------------------------------------------------------------------------------------

//______________________________________Setup_________________________________________________

void setup() {

  //LED Ring Setup------------------------------------------------------------------------------
  ring.begin(); //start the ring function
  ring.show(); //set up ability for LEDs to display
  ring.setBrightness(150); //can go up to 255


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
}

void selectedLED(uint32_t color) {

  bool flashOnce = false;
  
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
    delay(10000);
}


void optimusLED() {

  bool flash = false;
  
   if (flash != true) {

      ring.fill(ring.Color(225, 0, 0));
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 225));
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 0, 0));
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 225));
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 0));
      flash = true;
    }
  
    for(int i = 0; i < 7; i++){
      ring.setPixelColor(i, ring.Color(225, 0, 0));
      ring.show();
      delay(500);
    }
    for(int i = 6; i < 16; i++) {
      ring.setPixelColor(i+1, ring.Color(0, 0, 225));
      ring.show();
      delay(500);
    }
      delay(10000);
    
}


//_____________________________________Main Code___________________________________________________
void loop() {
  // put your main code here, to run repeatedly:


  //Idle LED Ring------------------------------------------------------------------------------------------------------
  
  idleLED();


  //NFC Code (Reading and printing the UID)-----------------------------------------------------------------------------

  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0}; //creates variable to store the tags UID
  uint8_t uidLength; //finds the legnth of the UID

  //used to make sure all four bytes of a tag match not just one as some uids have similar bytes
  uint8_t optimusCount = 0;
  uint8_t heatblastCount = 0;
  uint8_t alienXCount = 0;
  uint8_t clearCount = 0;


  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

//a loop to see if the uid that is read matches any of the tags required for each alien or the clear tag
  if (uidLength == 4 && success) {
    bool match = true;

    for (int i = 0; i < 4; i++) { // runs a loop for the length of the uid
      if (uid[i] == uidOptimus[i]) {
      optimusCount += 1;
      }
      else {
        optimusMatch = false;
      }
    }
    
    for (int i = 0; i < 4; i++) {
      if (uid[i] == uidHeatblast[i]) {
      heatblastCount += 1;
      }
      else {
        heatblastMatch = false;
      }
    }

    for (int i = 0; i < 4; i++) {
      if (uid[i] == uidAlienX[i]) {
      alienXCount += 1;
      }
      else{
        alienXMatch = false;
      }
    }

    for (int i = 0; i < 4; i++) {
      if (uid[i] == uidClear[i]) {
      
      clearCount += 1;
      }
      else{
        clearMatch = false;
      }
    }
  }


  if (optimusCount == 4){
    optimusMatch = true;
  }
  if (heatblastCount == 4) {
    heatblastMatch = true;
  }
  if (alienXCount == 4) {
    alienXMatch = true;
  }
  if (clearCount == 4) {
    clearMatch = true;
  }

//Logic system Depending on tags UID----------------------------------------------------------------------------
  
  //piezo state logic -------------------------------------------------------------------------------------------------
  bool Pressed = false;
  bool piezoStateChange = false;

  val = analogRead(0); //reads the current value of the piezo

  if ( val > 0.5 ) { //checks if the current value is above the threshold
    Pressed = true;
    piezoStateChange = true;
  }

  if ( val < 0.5 ) {
    Pressed = false;
    piezoStateChange = true;
  }
  

//-----------------------------------------------------------------------------------------------------------------------------

  if ((optimusMatch == true) && (Pressed == true)) {

    Serial.println(1);
    optimusLED();
    delay(300);
    //Serial.println("optimus");
    //LED Rings flash between Orange and white
  }

  if ((heatblastMatch == true) && (Pressed == true)) {

    Serial.println(2);
    //place LED Ring colour change and max subpatch route
    selectedLED(ring.Color(225, 120, 0));
    delay(300);
    //Serial.println("heatblast");
  }

  if ((alienXMatch == true) && (Pressed == true)) {

    Serial.println(3);
    //place LED Ring colour change and max subpatch route
    selectedLED(ring.Color(225, 0, 255));
    //Serial.println("Alien X");
    delay(300);
  }

  if ((clearMatch == true) && (Pressed == true)) {

    Serial.println(4);
    //place LED Ring colour change and max subpatch route
    selectedLED(ring.Color(225, 0, 0));
    delay(300);
   // Serial.println("cleared");
  }
}

