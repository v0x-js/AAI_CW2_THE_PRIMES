#define LEDPIN X
#define PIEZOTHRESHOLD 5;  // this is the analogue threshold for piezo sensing  


int PIEZOPIN = 2; 
int val; 

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
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
