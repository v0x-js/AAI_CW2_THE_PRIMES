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



//send number depending on NFC tag reading and the piezo sensor value exceeding the threshold 

if(val )
}
