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

uint8_t uidOptimus[] = {0x7A, 0xA1, 0x1A, 0xA3};
uint8_t uidHeatblast[] = {0xD6, 0x19, 0xF3, 0xFF};
uint8_t uidAlienX[] = {0xBA, 0x3E, 0x3A, 0xA3};
uint8_t uidClear[] = {0xD6, 0xAB, 0xD6, 0xFF};

bool optimusMatch = false;
bool heatblastMatch = false;
bool alienXMatch = false;
bool clearMatch = false;


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
  //for loop that runs for however many pixel leds there is (16 in this case), runs all individual LEDs sequentially and turns them off in the same order as previous loop
  //for(int j = 0; j < ring.numPixels(); j++){
    //ring.setPixelColor(j, ring.Color(0, 0, 0));
    //ring.show();
    //delay(100);
  //}
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
}
    //delay(100);
    //for(int i = 0; i < ring.numPixels(); i++){
      //ring.setPixelColor(i, ring.Color(0, 0, 0));
      //ring.show();
      //delay(100);
    //}
  //}



//_____________________________________Main Code___________________________________________________
void loop() {
  // put your main code here, to run repeatedly:

  //Idle LED Ring------------------------------------------------------------------------------------------------------
  
  idleLED();


  //NFC Code (Reading and printing the UID)-----------------------------------------------------------------------------

  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0}; //creates variable to store the tags UID
  uint8_t uidLength; //finds the legnth of the UID

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

//a loop to see if the uid that is read matches any of the tags required for each alien or the clear tag
  if (uidLength == 4 && success) {
    bool match = true;
    for (int i = 0; i < 4; i++) { // runs a loop for the length of the uid
  
      if (uid[i] == uidOptimus[i]) {
        optimusMatch = true;
      }
      if (uid[i] == uidHeatblast[i]) {
        heatblastMatch = true;
      }
      if (uid[i] == uidAlienX[i]) {
        alienXMatch = true;
      }
      if (uid[i] == uidClear[i]) {
        clearMatch = true;
      }
      if ((uid[i] != uidOptimus[i]) || (uid[i] != uidHeatblast[i]) || (uid[i] != uidAlienX[i]) || (uid[i] != uidClear[i])) {
        match = false;
      }
    }
  }

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

  if (optimusMatch == true && piezoStateChange == true && piezoStateChange == true) {

    selectedLED(ring.Color(225, 120, 0));

    //Sends message to max of what input to use
    Serial.println(1);
    Serial.println("optimus");
    delay(300);
    uint8_t uid[] = {0, 0, 0, 0};
    //LED Rings flash between Orange and white
  }

  if (heatblastMatch == true && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
    selectedLED(ring.Color(0, 0, 225));
    Serial.println(2);
    delay(300);
    Serial.println("heatblast");
    uint8_t uid[] = {0, 0, 0, 0};
  }

  if (alienXMatch == true && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
    Serial.println(3);
    delay(300);
  }
}

