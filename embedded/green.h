#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int _digitsum;
    int temp;
    int result;
    int _count;
    int pinno;
  public:
    green(int a);
    void active(int enano, int stepno);
    void Terminal(int enano, int stepno);
    void idle(int d, int e, int f);
    void tester(int d, int e, int f);
    int asciino(int d, int digit);
    int regional(int d);
};

#endif
