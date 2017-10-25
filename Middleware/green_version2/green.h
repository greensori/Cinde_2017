#ifndef green_h
#define green_h

#include "Arduino.h"

class green
{
  private:
    int _digitsum;
    int _pwm;
    int _ENA;
    int _DIR;
    int _STEP;
    int _Servo; //servo motor pi value
    int _pwmS; //savings servo angle status
    int _Potentio; // potentio pin no
    int _potentioSensor[4]; // savings recent potetiometer value
    int _pcount; //count for recording seprate values on potentio~[4]
    int _status; //for saving remain pwm
    int _d; 
    int _lv; //receiving present status
    int _i;
  public:
    green(int pulse, int EnaNo, int DirNo, int StepNo, int ServoNo, int PotenNo);
    int setting(int setvalue);
    void procWork(int Accel);
    void idle(int Accel, int peri);
    int asciino(char c1, int digit);
    int preader(); //read information from potentiometer
    int potentioavg(int poten);
};

#endif
