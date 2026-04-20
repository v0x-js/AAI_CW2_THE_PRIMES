#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ (2)
#define PN532_RESET (3)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  
  nfc.begin();
  
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Nae board fucknut");
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; //creates uid list with a max of seven inputs
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); //fills the success variable with tag data
  
  if (success){ //if success variable gets filled initiate if statement
    Serial.print(" UID Value: "); //prints string
    nfc.PrintHex(uid, uidLength); //prints the uid in hexadecimal format
    Serial.println("");//prints a space line
    delay(10000); //10 second delay

  }
  
}
