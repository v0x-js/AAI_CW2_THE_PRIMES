//ultimatrix script for NFC, Piezo pressure and led ring
//code for NFC reading based off of code found in PN532 Example library
//____________________________________for the librarys__________________________________________
//NFC Lirbary
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

//neopixel library
#include <Adafruit_Neopixel.h>

//______________________________________Definitions______________________________________________
//NFC Definitions
#define PN325_SCK (13)
#define PN532_MISO (12)
#define PN532_MOSI (11)
#define PN532_SS (10)

//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS); ignore this this is for a software connection but the arduino uno has hardware connections (keeping it here just in case though)
Adafruit_PN532 nfc(PN532_SS);


//Neopixel LED Definitions----------------------------------------------------------------
#define LED_PIN 6
#define LED_COUNT 16

Adafruit_Neopixel ring(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);


//Piezo Definitons------------------------------------------------------------------------
#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing  
int PIEZOPIN = 2; 
int val; 
//-----------------------------------------------------------------------------------------

//______________________________________Setup_________________________________________________

void setup() {

  //LED Ring Setup------------------------------------------------------------------------------
  ring.begin();
  ring.show();
  ring.setBrightness(50); //can go up to 255

  //NFC/RFID Setup------------------------------------------------------------------------------
  serial.begin(115200); //Initialises the serial communication with the computer
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Cannot find PN532 board");
    while(1);
  }

  //prints the information of detected PN532 RFID/NFC Module
  Serial.print("Found chip PN532"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver."); Serial.println((versiondata>>16) & 0xFF, DEC);

  Serial.println("Waiting for a card to be detected :3")

  //different types of tags have different lengths of UID this checks the length is 7bytes which is common to NTA203 tags
  if (uidLength == 7) {
    uint8_t data[32];
    
    Serial.println("Tag appears to be an NTA203 tag");
  }

}


//_____________________________________Main Code___________________________________________________
void loop() {
  // put your main code here, to run repeatedly:

  //Idle LED Ring------------------------------------------------------------------------------------------------------
  
  //for loop that runs for however many pixel leds there is (16 in this case)
  for (int i = 0; i< ring.numPixels(); i++) {
    ring.setPixelColour(i, (0), (255), (0), (0)); //colour code is in the order of R G B W
    ring.show();
    delay(50);
  }


  //NFC Code (Reading and printing the UID)-----------------------------------------------------------------------------

  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0 }; //creates variable to store the tags UID
  uint8_t uidLength; //finds the legnth of the UID

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO014443A, uid, &uidLength);

  if (success) {
    //information is displayed regarding the detected card
    Serial.print("ISO14443A Tag Detected!");
    Serial.print(" UID Length: "); Serial.print(uidLength, DEC); Serial.println("Bytes");
    Serial.print(" UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.print("");

  }


//Logic system Depending on tags UID----------------------------------------------------------------------------

  if (uid == "(Place UID Here)" && //place pizeo threshold code here) 
  {
    //place led colour change and max subpatch route
  }

  else if (uid == "(Place UID Here)") && //place pizeo threshold code here)
  {
    //place LED Ring colour change and max subpatch route
  }

  else if (uid == "(Place UID Here)") && //place pizeo threshold code here)
  {
    //place LED Ring colour change and max subpatch route
  }


pinMode(LEDPIN, OUTPUT); 
Serial.begin(9600); // Setting the serial baud rate



//send number to MAX depending on NFC tag reading if the piezo sensor value exceeds the threshold 

if ((val >= PIEZOTHRESHOLD) && RFID_Value1) { // These are the conditions for number being sent to MAX
  Serial.println(1);        // Sends the number 1 to select the correct voice modulator in MAX 9

}
if ((val >= PIEZOTHRESHOLD) && RFID_Value2) { // These are the conditions for number being sent to MAX
  Serial.println(2);        // Sends the number 2 to select the correct voice modulator in MAX 9

}
if ((val >= PIEZOTHRESHOLD) && RFID_Value3) { // These are the conditions for number being sent to MAX
  Serial.println(3);        // Sends the number 3 to select the correct voice modulator in MAX 9

}

}
