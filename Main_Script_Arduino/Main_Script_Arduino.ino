//ultimatrix script for NFC, Piezo pressure and led ring

//____________________________________for the librarys__________________________________________
//NFC Lirbary
#include <SPI.h>
#include <MFRC522.h>

//neopixel library
#include <Adafruit_Neopixel.h>

//______________________________________Definitions______________________________________________
//NFC Definitions
#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

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
serial.begin(9600); //Initialises the serial communication with the computer
SPI.begin(); //Initialises the SPI Bus
mfrc522.PCD_Init(); //Initialises the MFRC522 itself

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

  //Looks for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  //Selects one of the cards
  if (! mfrc255.PIC_ReadCardSerial()) {
    return;
  }

  //Shows the UID on the monitor
  Serial.print("UID tag - ");
  String content = "";
  byte letter;

  //runs a for loop the size of the UID
  for (byte i = 0; i<mfrc522.uid.size; i++) { 
  //prints the UID one by one in Hex format
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);

    //stores the data into the content variable
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));   
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase


//Logic system Depending on tags UID----------------------------------------------------------------------------

  if (content.substring(1) =="(Place UID Here)" && //place pizeo threshold code here) 
  {
    //place led colour change and max subpatch route
  }

  else if (content.substring(1) =="(Place UID Here)") && //place pizeo threshold code here)
  {
    //place LED Ring colour change and max subpatch route
  }

  else if (content.substring(1) =="(Place UID Here)") && //place pizeo threshold code here)
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
