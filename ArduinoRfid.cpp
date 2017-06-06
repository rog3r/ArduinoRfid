#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Converter.h>
#include "ArduinoRfid.h"

Converter conversorLib;
String rfidNewTag = "";
String rfidTagFound = "";
int ConversorBauldRate= 9600;

ArduinoRfid::ArduinoRfid(SoftwareSerial *serial){
 softwareSerial = serial;
}

/*
  Function Name: startRFID
  Description: Starts the hardware and software serial ports
*/
void ArduinoRfid::startRFID(int bauldRate) {
  ConversorBauldRate = bauldRate;
  Serial.begin(bauldRate);
  softwareSerial->begin(bauldRate);
  Serial.println("===== Aproxime o cartao! =====");
}

/*
  Function Name: stopRFID
  Description: Stop the hardware and software serial ports
*/
void ArduinoRfid::stopRFID() {
  Serial.end();
  softwareSerial->end();
}

/*
  Function Name: cartaoNaoLido
  Description: Return true if 
*/
boolean ArduinoRfid::cardNotRead() {
  return rfidTagFound.equals("");
}

/*
  Function Name: readTag
  Description: read new tag with size (tagLen) 
*/
String ArduinoRfid::readTag(const int tagLen) {

Wait_Loop: 
  int i = 1;
  if (softwareSerial->available() == tagLen) {  // This makes sure the whole tag is in the serial buffer before reading, the Arduino can read faster than the ID module can deliver!   
	  if (cardNotRead()) {
	      Serial.println("Lendo Cartao");
		  while (softwareSerial->available() && i < tagLen) {  // Take each byte out of the serial buffer, one at a time
	        char c = softwareSerial->read();
	        if (validChar(c)) {
	          rfidNewTag += c;
	          i++;
	        }
	        if (endLine(c) || i == tagLen) {// If we see ASCII 3, ETX, the tag is over
	          Serial.print("Cartao Lido: ");
	          Serial.println(rfidNewTag);
	          Serial.print("Matricula: ");
	          Serial.println(conversorLib.hexToDecString(rfidNewTag));
	          rfidTagFound = rfidNewTag;
	          rfidNewTag = "";	        
	          return rfidTagFound;
	        }
		 }
	  }    
	  
   }
   if (!cardNotRead()) {
   	 rfidTagFound = "";
   	 delay(1000);
   	 resetRFID(ConversorBauldRate); 
	 goto Wait_Loop;
   }  
    
  return rfidTagFound;
}

/*
  Function Name: resetRFID
  Description: Stop and starts the hardware and software serial ports
*/
void ArduinoRfid::resetRFID(int bauldRate) {
  stopRFID();
  startRFID(bauldRate);
}

/*
  Function Name: endLine
  Description: Return true if is tag endline
*/
boolean ArduinoRfid::endLine(char c) {
  return (c == '\n') || (c == '\r') ;
}

/*
  Function Name: validChar
  Description: Return true if is valid char to fill tag card
*/
boolean ArduinoRfid::validChar(char c) {
  return (c >= 32) && (c <= 126);
}


