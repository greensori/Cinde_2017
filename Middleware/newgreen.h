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
  public:
    green(int EnaNo, int DirNo, int StepNo);
    void setiing(int sta);
    void idle(int Accel);
    int asciino(int d, int digit);
};

#endif
