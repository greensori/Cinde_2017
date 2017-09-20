#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int temp;
    int pinno;
  public:
    green(int a);
    void active(int enano, int stepno);
    void Terminal(int enano, int stepno);
    void idle(int d, int e, int f);
    int digitno(char c, int digit);
};

#endif
