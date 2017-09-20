#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int temp;
    int _i;
  public:
    green(int a);
    void active(int enano, int stepno);
    void Terminal(int enano, int stepno);
    void idle(int STEP, int sleep);
    int digitno(char c, int digit);
};

#endif
