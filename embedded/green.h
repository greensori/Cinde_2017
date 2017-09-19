#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int _pin;
    int i;
  public:
    green(int sumStep);
    void on(int STEP);
    void ter(int ENA, int STEP);
    void idle(int STEP, int sleep);
};

#endif
