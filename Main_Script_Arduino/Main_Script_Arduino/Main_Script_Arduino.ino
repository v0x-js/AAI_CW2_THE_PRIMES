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

//creates reference uids for the tags being used (they are all 4bytes)
uint8_t uidOptimus[] = {0x7A, 0xA1, 0x1A, 0xA3};
uint8_t uidHeatblast[] = {0xD6, 0x19, 0xF3, 0xFF};
uint8_t uidAlienX[] = {0xE2, 0x00, 0x10, 0x10};
uint8_t uidClear[] = {0xD6, 0xAB, 0xD6, 0xFF};

// Set to false by default and used to keep track for logic later in the algorithm
bool optimusMatch = false;
bool heatblastMatch = false;
bool alienXMatch = false;
bool clearMatch = false;


//NeoPixel LED Definitions----------------------------------------------------------------
#define LED_PIN 6 //which pin the data line is plugged into
#define LED_COUNT 16 //defines how manyleds are in the strip/ring in this case
//bool flashOnce = false;
bool idle = true;

// create function for the LED ring
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //number of LEDs on ring, pin connection, define specific model (RGBW), define data rate


//Piezo Definitons - xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Due to wiring issues we had to remove the piezoelectric sensor from the system, this is the proof that the code worked :)

//#define PIEZOTHRESHOLD 0.5;  // this is the analogue threshold for piezo sensing (subject to change on testing likley will be higher number)  
//#define PADNUM 1 //1 pad in the analogue pins

// setting default values for watch press + creating variables for watch press
//int val; // used to store value of current piezo sensor input to check if threshold for piezo sesnor is being exceeded or not
 //variable to say if piezo is being pushed or released
//bool piezoPrevState = false;  //allows for comparison to previous state
 // has there been a change in the state - true or false

// - xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//______________________________________Setup_________________________________________________

void setup() {

  //LED Ring Setup------------------------------------------------------------------------------
  ring.begin(); //start the ring function
  ring.show(); //set up ability for LEDs to display
  ring.setBrightness(167); //can go up to 255


  //NFC/RFID Setup------------------------------------------------------------------------------
  Serial.begin(115200); //Initialises the serial communication with the computer
  nfc.begin(); //begin nfc function


 //constant check for nfc board being connected to notify of error
  uint32_t versiondata = nfc.getFirmwareVersion(); // checks for the boards firmware for proof its connected
  if (!versiondata) { // conditional if statment
    Serial.print("Cannot find PN532 board");
    while(1); //stops the code
  }
}

//_____________________________________Light Sequence Functions_________________________________

//the initial loading and base colour for the ultimatrix
void idleLED(){
  for(int i = 0; i < ring.numPixels(); i++){ //creates a loop based on how many pixels are in the ring (16 pixels)
  ring.setPixelColor(i, ring.Color(0, 225, 0)); //sets the pixel selected by the counter  to the colour green
  ring.show(); //displays/updates on the ring 
  delay(100);
  }
}

//for the clear tag this function flashes red and then loads and stays for 10 seconds 
void timeoutLED(uint32_t color) { //the function selects the colour when calling the function as this was originally used for all of the tags however this still llows more customisation if wanted

  bool flashOnce = false; // used so if it runs multiple times it doesnt keep flashing and not run the other stuff in the funtion

   if (flashOnce != true) {

    //sets all the pixels to the selected colour at once
      ring.fill(color);
      ring.show();
      delay(150);

      //sets all the pixels to off at once
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

    //for loop runs for the amount of pixels in the ring and sequentially turns on each pixel led
    for(int i = 0; i < ring.numPixels(); i++){
      ring.setPixelColor(i, color);
      ring.show();
      delay(100);
    }
    delay(10000); //lasts for 10 seconds
}

//custom LED sequence function for optimus prime tag
void optimusLED() {

  //as before the flash code works the same as above except it flashes between blue and red
  bool flash = false;
  
   if (flash != true) {

      ring.fill(ring.Color(225, 0, 0));//red colour
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 225));//blue colour
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 0, 0));//red colour
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 225));//blue colour
      ring.show();
      delay(150);

      ring.fill(ring.Color(0, 0, 0));
      flash = true;
    }

    //runs for the first half of the pixel leds and sequentially turns them red
    for(int i = 0; i < 7; i++){
      ring.setPixelColor(i, ring.Color(225, 0, 0));
      ring.show();
      delay(500);
    }

    //runs for the latter half of the pixels and sequentially turns them blue
    for(int i = 6; i < 16; i++) {
      ring.setPixelColor(i+1, ring.Color(0, 0, 225));
      ring.show();
      delay(500);
    }
      delay(10000); //keeps the leds on for 10 seconds
    
}

//heatblast custom function for light sequence mimmicking a fire crackle
void heatblastLED(){

  bool flashOnce = false;//used for flash logic to avoid repitition
  int speed = 30; //variable used to control the speed of the fire flicker

  if (flashOnce != true) {

      ring.fill(0,0, 0);
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 34, 0));//orange colour
      ring.show();
      delay(150);

      ring.fill(0, 0, 0);
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 34, 0)); //orange colour
      ring.show();
      delay(150);
      flashOnce = true;
    }

  //runs for 59 cycles as that means the sequence lasts for around 10 seconds 
  for (int i = 0; i <59;i++){
    int pixel = random(LED_COUNT);//sets a random number for selection of the pixel
    ring.setPixelColor(pixel, 225, 34, 0); //sets the base colour of the wtch
    ring.show();
    delay(20);
    ring.setPixelColor(pixel, 225, random(0, 100), 0);//causes a random pixel to change shade of orange via a random in the green section ranging from 0 to 100 as any higher makes the yellow quite unpleasing
    ring.show();
    delay(speed);
    
    //repeats the previous section but has it so multiple pixels are changing at once for a nicer effect
    //these include random red pixels as well as yellow ones
    int pixelTwo = random(LED_COUNT);
    ring.setPixelColor(pixelTwo, 225, 34, 0);
    ring.show();
    delay(20);
    ring.setPixelColor(pixelTwo, random(150, 225), random(0, 50), 0);
    ring.show();
    delay(speed);
    
    int pixelThree = random(LED_COUNT);
    ring.setPixelColor(pixelThree, 225, 34, 0);
    ring.show();
    delay(20);
    ring.setPixelColor(pixelThree, random(150, 225), random(0, 50), 0);
    ring.show();
    delay(speed);
  }
}

//alien x custom light sequence 
void alienXLED(){
  //same flash sequence at the starts of every light sequence
  bool flashOnce = false;

  if (flashOnce != true) {

      ring.fill(0,0, 0);
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 0, 225));
      ring.show();
      delay(150);

      ring.fill(0, 0, 0);
      ring.show();
      delay(150);

      ring.fill(ring.Color(225, 0, 225));
      ring.show();
      delay(150);
      flashOnce = true;
    }
  
  //creates a theatre chase effect but instead of the third pixels being off it is a damper shade of lavender colour for a space twinkle kind of effect
  for (int i=0; i<16; i++) {  //runs for 16 cycles as that runs for around 10 seconds when factoring in delays
    for (int j=0; j < 3; j++) {
      for (int k=0; k < LED_COUNT; k=k+3) { //turns every third led pixel to the lighter/brighter colour
        ring.setPixelColor(k+j, 225,0,225);   //k+j creates the third pixel location
      }
      ring.show();
     
      delay(200);
     
      for (int k=0; k < LED_COUNT; k=k+3) {//creates a loop for turns every other third pixel to the lower shade of lavender
        ring.setPixelColor(k+j, 100,0,100);    //darker shade of lavender
      }
    }
  }
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

  //used to make sure all four bytes of a tag match not just one as some uids have similar bytes - this is set up by a counter
  uint8_t optimusCount = 0;
  uint8_t heatblastCount = 0;
  uint8_t alienXCount = 0;
  uint8_t clearCount = 0;


  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); //reads the uid of the detected tag into the created variable

//a loop to see if the uid that is read matches any of the tags required for each alien or the clear tag
  if (uidLength == 4 && success) {
    bool match = true;

    //// these for loops run for the length of the uid and compare each byte with the byte of the referene uids created at the start of the code
    //if a byte matches it adds one to the counter of that specific alien if they dont match it sets the whole match for that aliens tag uid reference to false
    for (int i = 0; i < 4; i++) { 
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
//end of uid check for loops

//creates conditional statments so only when all 4 bytes of the uid match the alien tags reference uid will it say that the tags match and run the subsequent code
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
//-----------------------------------------------------------------------------------------------------------------------------


//________________________________________________Logic system Depending on tags UID___________________________________________________

  if ((optimusMatch == true)) {//checks if the uid matches

    Serial.println(1);//prints integer one and sends it through the serial path to max 
    optimusLED();//calls the custom optimus led sequence function
    delay(300);//creates a delay so theres no accidental double sends

    //Serial.println("optimus"); used for testing
  }

  if ((heatblastMatch == true)) {//checks if the uid matches

    Serial.println(2);//prints integer two and sends it through the serial path to max 
    heatblastLED();//calls the custom heatblast light sequence
    delay(300);//creates a delay so theres no accidental double sends

    //Serial.println("heatblast");used for testing
  }

  if ((alienXMatch == true)) {//checks if the uid matches

    Serial.println(3);//prints integer three and sends it through the serial path to max 
    alienXLED();//calls the custom light sequence for alien x
    delay(300);//creates a delay so theres no accidental double sends
    //Serial.println("Alien X");used for testing

  }

  if ((clearMatch == true)) {//checks if the uid matches

    Serial.println(4);//prints integer four and sends it through the serial path to max 
    timeoutLED(ring.Color(225, 0, 0));//calls the custom tmieour light sequence function and sets the colour to red
    delay(300);//creates a delay so theres no accidental double sends
   // Serial.println("cleared");used for testing
  }
}

