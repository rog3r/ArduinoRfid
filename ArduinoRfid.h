#ifndef ArduinoRfid_h
#define ArduinoRfid_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class ArduinoRfid
{
  public: 
    ArduinoRfid(SoftwareSerial *serial);
    void startRFID(int bauldRate);
    void stopRFID();
    boolean cardNotRead();
    String readTag(const int tagLen);
    void resetRFID(int bauldRate);
    boolean endLine(char c);
    boolean validChar(char c);
  private:
  	SoftwareSerial * softwareSerial;
};

#endif
