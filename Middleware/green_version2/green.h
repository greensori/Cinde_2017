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
  public:
    green(int EnaNo, int DirNo, int StepNo, int pulse);
    int setting(int setvalue);
    void idle(int Accel);
    int asciino(char c1, int digit);
    int chconverter(char ch);
};

#endif
