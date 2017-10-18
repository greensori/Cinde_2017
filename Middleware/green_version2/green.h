#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int _digitsum;
    int _pulse;
    int _ENA;
    int _DIR;
    int _STEP;
    int _status;
    int _d;
    int _i;
  public:
    green(int EnaNo, int DirNo, int StepNo, int pulse);
    int setting(int setvalue);
    void procWork(int Accel);
    void idle(int Accel, int peri);
    int asciino(char c1, int digit);
    int chconverter(char ch);
};

#endif
