//ultimatrix script for NFC, Piezo pressure and led ring
//code for NFC reading based off of code found in PN532 Example library
//____________________________________for the librarys__________________________________________
//NFC Lirbary
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

//neopixel library
#include <Adafruit_NeoPixel.h>

//______________________________________Definitions______________________________________________
//NFC Definitions, defining the pins for the NFC Reader
#define PN325_SCK (13)
#define PN532_MISO (12)
#define PN532_MOSI (11)
#define PN532_SS (10)

//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS); ignore this this is for a software connection but the arduino uno has hardware connections (keeping it here just in case though)
Adafruit_PN532 nfc(PN532_SS); //defining the relationship/connection between the arduino board and the PN532


//NeoPixel LED Definitions----------------------------------------------------------------
#define LED_PIN 6
#define LED_COUNT 16

// create function for the LED ring
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800); //number of LEDs on ring, pin connection, define specific model (RGBW), define data rate


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
  if (! versiondata) {
    Serial.print("Cannot find PN532 board");
    while(1);
  }

  //prints the information of detected PN532 RFID/NFC Module
  Serial.print("Found chip PN532"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver."); Serial.println((versiondata>>16) & 0xFF, DEC);

  Serial.println("Waiting for a card to be detected :3");

}


//_____________________________________Main Code___________________________________________________
void loop() {
  // put your main code here, to run repeatedly:

  //Idle LED Ring------------------------------------------------------------------------------------------------------
  
  //for loop that runs for however many pixel leds there is (16 in this case), runs all individual LEDs sequentially
  for (int i = 0; i< ring.numPixels(); i++) {
    ring.setPixelColor(i, (0), (255), (0), (0)); //colour code is in the order of R G B W
    ring.show();
    delay(50);
  }


  //NFC Code (Reading and printing the UID)-----------------------------------------------------------------------------

  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0 }; //creates variable to store the tags UID
  uint8_t uidLength; //finds the legnth of the UID

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    //information is displayed regarding the detected card
    Serial.print("ISO14443A Tag Detected!");
    Serial.print(" UID Length: "); Serial.print(uidLength, DEC); Serial.println("Bytes");
    Serial.print(" UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.print("");

 //different types of tags have different lengths of UID this checks the length is 7bytes which is common to NTA203 tags
  if (uidLength == 7) {
    uint8_t data[32];
    
    Serial.println("Tag appears to be an NTA203 tag");
  }
  }


//Logic system Depending on tags UID----------------------------------------------------------------------------
  
  //piezo state logic
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
  
  if (uid == "(Place UID Here)" && piezoStateChange == true) {

    //place led colour change and max subpatch route

    if (piezoStateChange == false) { //the watch dial is in the up position whenever the state change is false 
      //slector 4 for timout
    
    }
  }

  else if (uid == "(Place UID Here)" && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
  }

  else if (uid == "(Place UID Here)" && piezoStateChange == true) {
    //place LED Ring colour change and max subpatch route
  }




}
