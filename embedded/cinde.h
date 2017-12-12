#ifndef cinde_h
#define cinde_h

#include "Arduino.h"

class cinde
{
  private:
    int _stepinfo[3]; //ena, dir, steps
    int _count;
    int _analogNo;
    int _maxAnalog;
    int _digitsum; //using in asciino
    int _d; //using in asciino
    int _digit;
    int _workingStep;
    int _status;
  public:
    cinde(int maxAnalog);
    void stepwork(int stepno);
    void stepstatus(int ena, int dir, int stepno);
    void statuschanger(int count);
    int analogReader(int rest, int Analog);
    int asciino(char c1, int stepping);   
    void tester();
};

#endif
