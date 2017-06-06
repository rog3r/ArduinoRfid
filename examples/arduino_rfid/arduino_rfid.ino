#include <SoftwareSerial.h> 
#include <ArduinoRfid.h>

#define RFID_RX 65
#define RFID_TX 64

SoftwareSerial RFID(RFID_RX, RFID_TX);// Choose two pins for SoftwareSerial // RX, TX
ArduinoRfid rfid(&RFID); //Passing by reference softwareSerial instance

const int tagLen = 11;
String tagFound = "";
int bauldRate = 9600;

void setup() { // Starts the hardware and software serial ports
  rfid.startRFID(bauldRate);
}

boolean cardNotFound() {
  return tagFound.equals("");
}

void loop() { 
Wait_Card:
  if (cardNotFound()) {
    tagFound =  rfid.readTag(tagLen);
  } else {
    testEsd();
  } 
  goto Wait_Card;
}

void testEsd() {
  for (int i = 0; i < 7; i++) {
    delay(1000);
    Serial.print("Aguardando...");
    Serial.println(i);
  }
  tagFound = "";
}


