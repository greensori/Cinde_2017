#ifndef cinde_h
#define cinde_h

#include "Arduino.h"

class cinde
{
  private:
    int _count;
    int _analogNo;
    int _maxAnalog;
    int _ascii;
  public:
    cinde(int maxAnalog);
    void stepwork(int stepno);
    void stepoff(int stepno, int ena);
    int analogReader(int rest, int Analog);
    int asciichanger(char c);
    
};

#endif
