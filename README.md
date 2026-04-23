# AAI_CW2_THE_PRIMES
This is 'THE PRIMES' Audio and Interactivity CW2 Project. We have built a recreation of the 'Ultamatrix' seen in Ben 10, featuring custom sound effects for usage of the watch, and a voice changer that corresponds to the chosen monster. These monsters are selected via a PN532 RFID scanner and 4 corresponding tags (3 of which correspond to our monsters, and one of which is a clear tag.)

------
EXPLANATION OF FILES AND FOLDERS - 
Main_Script_Arduino 
 - Main_Script_Arduino - all main arduino code 
 - piezo_baseCode (made a subfolder as errors were encountered when all arduino scripts were in 1 folder)
 - - piezoComTest - testing arduino code for troubleshooting the pressure sensor logic
 - PN532_baseCode (subfolder made for same reason as piezoComTest)
 - - PN532_baseCode - initial coding for RFID shield use with arduino, kept for backups
 Main_Script_Max - 
 - Max_Patch_Main - all max code that arduino code will run into - includes multiple subpatches for 
 - Audio Files 
 - - ultamatrix_timeout.mp3 - used if the sensor is hit after the 'clear' tag was scanned 
 - - [REDACTED].wav - used for boot up for [REDACTED]

------
INSPIRATIONS AND RESOURCES -
- https://www.youtube.com/watch?v=wt5Srn2C0A4 - used for fire sound for heat blast 
- previous coursework - Jamie's APE CW2 was repurposed for reverb effect
- https://www.youtube.com/watch?v=wD7KHzpFBvw - inspiration for 'flame burst' on-hit effect
- https://www.youtube.com/watch?v=uyzY_ZP54pA&list=PLD45EDA6F67827497&index=8 - used for [REDACTED] phaser 
- https://learn.adafruit.com/adafruit-pn532-rfid-nfc/arduino-library - info on PN532 component use
- https://docs.arduino.cc/libraries/adafruit-neopixel/ - LED ring component info 
- https://medium.com/@elonskolnik/arduino-uno-tutorial-neopixel-ring-setup-9fafc099c89a - Neopixel LED setup tutorial 
- https://www.youtube.com/watch?v=8YCoigIOOxU - RFID video - watched when troubleshooting shield issues
- https://www.youtube.com/watch?v=6bT3G4Mep7E - shows how to connect max and arduino code
- previous coursework - Ella's APE CW2 was used for ring modulation and chorus
